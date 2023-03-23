#include "header.hpp"
#include <cstdint>

/*
This function will initialize an empty node strucutre, provided a pointer to that strucutre
*/
bool init_node(struct Node* node){
    node->id  = 0;                  // default id value 0
    node->gid = 0;                  // default gid value 0
    node->index = 0;                // default entry count 0
    node->data_base;                // default empty array THIS WILL LIKELY NEED TO BE AMENDED
   
    /* check that each item is set to what we want it intialized to e.g., !node->id, we set it to 0, so this should 
       evaluate to 1.
    */
    if ((!node->id) && (!node->gid) && (!node->db_entry_count) && (sizeof(node->data_base) == 0)){
        return true;
    } 
    DEBUG_PRINT("Error initializing node...\n");
    return false;
};

bool set_node_id(struct Node* node, uint8_t id){
    node->id = id; 
    return node->id == id;
};

bool set_node_gid(struct Node* node, uint16_t gid){
    node->gid = gid; 
    return node->gid == gid;
};

// NOTE: count can be a uint8_t because it goes to 255 and the count will never exceed 40
bool set_node_db_entry_count(struct Node* node, uint8_t count){
    node->index = count; 
    return node->index == count;
};


// reset neighbouring node array
void reset_array(struct Node* node) {
	for (int i=0; i<NNODE_GROUP_SIZE; i++) {
		node->nnodes[i] = 0;
	}
}

// Generate random value between 0-255
uint8_t generate_request_num(void){
    return (uint8_t) (rand() % 255);
}

// returns false when full, true when it succesfully inserts record...
bool insert_record(struct Node *node, char* new_entry, uint8_t owner_id){

    // if the item count is 40, our database for this node is full...
    if (node->data_base.item_count == NUMB_OF_ENT){
        return false;
    } else {
        // the item count is not 40, and since other user can randomly delete entries, we will just iterate from
        // 0 till we find the first null entry.
        for (int i = 0; i < NUMB_OF_ENT; i++){
            if (node->data_base.item_array[i].data_entry == '\0'){
                strncpy(node->data_base.item_array[i].data_entry, new_entry, sizeof(new_entry)); 
                node->data_base.item_array.owner_id = owner_id;
                // TODO: get time stamp...
                node->data_base.item_array.timestamp = 0;
                node->data_base.item_count += 1;
            };
        };
    };
    
    //TODO: add check that the operation was succesful 
    return true;   
};

// returns false when 0 items in db or the index is already null, otherwise true after deletion
bool delete_record(struct Node *node, uint8_t index){

    // empty database, or empty index, can't delete record
    if (node->data_base.item_count == 0 || node->data_base.item_array[index].data_entry == '\0'){
        return false;
    } else{
        // NOTE: This may complain
        node->data_base.item_array[index].data_entry = '\0';
        node->data_base.item_array.timestamp = NULL;
        node->data_base.item_count -= 1;
    };
    
    //TODO: add check that the operation was succesful 
    return true;
};

char* retrieve_record(struct Node *node, uint8_t index){

    return node->data_base.item_array[index].data_entry;

};