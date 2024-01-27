#include <arena.h>
#include <ctype.h>
#include <linkedlist.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "scanner.h"
#include "parser.h"
#include "hashtable.h"

JSONPair* json_pair_create(Arena* arena) {
  JSONPair* new_pair = arena->alloc(arena,sizeof(JSONPair));
  new_pair->current_value = false;
  new_pair->key_length = 0;
  return new_pair;
}

JSONObj* json_object_create(Arena* arena) {
  JSONObj* json_object = arena->alloc(arena, sizeof(JSONObj));
  HashTable objects;
  hashtable_init(&objects, 100, arena);
  json_object->objects = objects;
  json_object->current_object = true;
  return json_object;
}

LinkedList* linkedlist_create(Arena* arena) {
  LinkedList* linked_list = arena->alloc(arena, sizeof(LinkedList));
  linked_list_init(linked_list, arena);
  return linked_list;
}

bool isescaped(char current_character) {
  char escape_characters[] = {'"','\n','\t','\v','\f','\r'};
  int array_length = 6;
  
  int i = 0;
  while(i < array_length) {
    if(current_character == escape_characters[i]) {
      return true;
    }
    i++;
  }

  return false;
}

JSONObj* parse_json(JSONBuffer* json_buffer, Arena* arena) {

    JSONPair* json_pair = json_pair_create(arena);

    JSONObj* json = NULL;

    bool was_bracketed = false;

    char current_character;

    while(json_buffer->current_position < json_buffer->file_size-1 && !json_buffer->error) {
      
      current_character = json_buffer->current_file[json_buffer->current_position];
    
      if(isdigit(current_character) && json_pair->current_value) {
        json_pair->data_type = NUM;
        json_pair->data.num = parse_number(json_buffer, arena);

        json_pair->value_exists = true;
        json_pair->current_value = false;
        continue;
      }

      if(was_bracketed && !isspace(current_character) && current_character != '"' && current_character != '{' && current_character != '}') {
        json_buffer->error = true;
      }

      if(current_character == '{') {
        if(json == NULL) {
          json = json_object_create(arena);
          was_bracketed = true;
        }
        else {
          JSONObj* nested_json = parse_json(json_buffer,arena);
          
          json_pair->data_type = JSON;
          json_pair->data.json = nested_json;
          json_pair->current_value = false;
          continue;
        }
      }

      if(current_character == '[' && json_pair->current_value) {
        json_buffer->current_position++;
        json_pair->data.array = parse_array(json_buffer, arena);

        json_pair->data_type = ARRAY;
        json_pair->value_exists = true;
        json_pair->current_value = false;
        continue;
      }

      if(current_character == '"' && json->current_object) {
        if(json_pair->key_length == 0) {
          parse_key(json_buffer,json_pair);
          was_bracketed = false;
          continue;
        }
        else if(json_pair->current_value) {
          json_pair->data.str = parse_string(json_buffer,arena);

          json_pair->data_type = STR;
          json_pair->value_exists = true;
          json_pair->current_value = false;
          continue;
        }
      }

      if(current_character == ':' && json_pair->key_length > 0) {
        json_pair->current_value = true;
      }

      if(current_character == ',') {
        if(json_pair->value_exists && json_pair->key_length > 0) {
          json->objects.methods->insert(&json->objects,json_pair->key,json_pair->key_length,json_pair);
          json_pair = json_pair_create(arena);
        } 
        else if(json->current_object) {
          json_buffer->error = true;
          continue;
        }
      }

      if(current_character == '}' && json != NULL){
        if(json_pair->key_length > 0 && json_pair->value_exists) {
          json->objects.methods->insert(&json->objects,json_pair->key, json_pair->key_length,json_pair);
        }
        json->current_object = false;
        json_buffer->current_position++;
        break;
      }

      json_buffer->current_position++;
    }
    
    if(json == NULL) {
      json_buffer->error = true;
    }
    
    return json;
}

void parse_key(JSONBuffer* json_buffer, JSONPair* current_json) {
  json_buffer->current_position++;
  char current_character;
  bool was_escaped = false;
  
  while(true) {
    current_character = json_buffer->current_file[json_buffer->current_position];
  

    if(json_buffer->current_position + 1 == json_buffer->file_size) {
      json_buffer->error = true;
      return;
    }

    if(isescaped(current_character) && !was_escaped) {
      if(current_character != '"') {
        json_buffer->error = true;
        return;
      }
    }

    if(current_character == '"' && !was_escaped) {
      break;
    }

    if(current_character == '\\') {
      was_escaped = true;
    }

    if(current_json->key_length < 256) {
      current_json->key[current_json->key_length] = current_character;
      current_json->key_length++;
      json_buffer->current_position++;
    }
    else {
      json_buffer->error = true;
      return;
    }

    if(isescaped(current_character) && was_escaped) {
      was_escaped = false;
    } 
  }
  json_buffer->current_position++;
}

LinkedList* parse_string(JSONBuffer* json_buffer, Arena* arena) {
  
  json_buffer->current_position++; 
  LinkedList* string = linkedlist_create(arena);
  char current_character;
  bool was_escaped = false;

  while(true) {
    current_character = json_buffer->current_file[json_buffer->current_position];
    if(json_buffer->current_position+1 == json_buffer->file_size) {
      json_buffer->error = true;
      return NULL;
    }

    if(isescaped(current_character) && !was_escaped) {
      if(current_character != '"') {  
        json_buffer->error = true;
        return NULL;
      }
    }

    if(current_character == '"' && !was_escaped) {
      break;
    }

    if(current_character == '\\') {
      was_escaped = true;
    }

    char* current_char = arena_alloc(arena, sizeof(char));
    current_char[0] = json_buffer->current_file[json_buffer->current_position];

    string->methods->insert(string, current_char);

    if(isescaped(current_character) && was_escaped) {
      was_escaped = false;
    }

    json_buffer->current_position++;
    }
  
  json_buffer->current_position++;
  return string;
}

JSONNum* parse_number(JSONBuffer* json_buffer, Arena* arena) {
  JSONNum* number = arena->alloc(arena, sizeof(JSONNum));
  number->length = 0;
  char current_character = json_buffer->current_file[json_buffer->current_position];

  while(isdigit(current_character) || isxdigit(current_character) || current_character == '.') {
    if(json_buffer->current_position+1 == json_buffer->file_size) {
      json_buffer->error = true;
      return NULL;
    }
    
    if(number->length <= 64) {
      number->value[number->length] = current_character;
      number->length++;
    }
    else {
      json_buffer->error = true;
      return NULL;
    }
    
    json_buffer->current_position++;
    current_character = json_buffer->current_file[json_buffer->current_position];
  }

  return number;
}


LinkedList* parse_array(JSONBuffer* json_buffer, Arena *arena) {
  LinkedList* array = linkedlist_create(arena);
  char current_character = json_buffer->current_file[json_buffer->current_position];
  
  bool was_comma = false;

  ArrayData* array_member = arena->alloc(arena, sizeof(ArrayData));

  while(current_character != ']') {
    
    current_character = json_buffer->current_file[json_buffer->current_position];

    if(json_buffer->error) {
      return NULL;
    }

    if(json_buffer->current_position+1 == json_buffer->file_size) {
      json_buffer->error = true;
      return NULL;
    }

    if(isdigit(current_character)) {
      if(array->length == 0 || was_comma) {
        array_member->data_type = NUM;
        array_member->data.num = parse_number(json_buffer, arena);
        array->methods->insert(array, array_member);

        array_member = arena->alloc(arena, sizeof(ArrayData));
        was_comma = false;
        continue;
      }
      else {
        json_buffer->error = true;
      }
    }

    if(current_character == '[') {
      if(array->length == 0 || was_comma) {
        array_member->data_type = ARRAY;
        json_buffer->current_position++;
        array_member->data.array = parse_array(json_buffer, arena);
        array->methods->insert(array, array_member);

        array_member = arena->alloc(arena, sizeof(ArrayData));
        was_comma = false;
        continue;
      }
      else {
        json_buffer->error = true;
      }
    }

    if(current_character == '{') {
      if(array->length == 0 || was_comma) {
        array_member->data_type = JSON;
        array_member->data.json = parse_json(json_buffer,arena);
        array->methods->insert(array, array_member);

        array_member = arena->alloc(arena, sizeof(ArrayData));
        was_comma = false;
        continue;
      }
      else {
        json_buffer->error = true;
      }
    }

    if(current_character == '"') {
      if(array->length == 0 || was_comma) {
        array_member->data_type = STR;
        array_member->data.str = parse_string(json_buffer,arena);
        array->methods->insert(array, array_member);

        array_member = arena->alloc(arena, sizeof(ArrayData));
        was_comma = false;
        continue;
      }
      else {
        json_buffer->error = true;
      }
    }


    if(current_character == ',') {
      if(array->length != 0) {
        was_comma = true;
      }
      else {
        json_buffer->error = true;
      }
    }

    json_buffer->current_position++;
  }

  return array;
}

