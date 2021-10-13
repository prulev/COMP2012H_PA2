#include "Commit.h"
#include "Utils.h"

using namespace std;

// Part 1: Linked List Operations

List *list_new() {


    List* list= new List;

    list -> head = new Blob;

    list->head->name = "";
    list->head->ref = "";
    list->head->commit = nullptr;
    list->head->next = list->head;
    list->head->prev = list->head;

    return list;
}

void list_push_back(List *list, Blob *blob) {

    if(list!=nullptr && blob!=nullptr){

        Blob* tail = list->head->prev;  //"tail" points to the current end of the linked list

        blob->next = list->head;
        blob->prev = tail;

        tail->next = blob;

        list->head->prev = blob;
    }
}

Blob *list_find_name(const List *list, const string &name) {

    if(list!= nullptr){
        for (Blob* blob = list->head->next; blob != list->head ; blob = blob->next)
        {
            if(blob->name == name){ //差点写错==，小心！
                return blob;
            }
        }
        return nullptr;
    }
    return nullptr;
}

Blob *list_put(List *list, const string &name, const string &ref) {

    if(list!=nullptr ){
            
        //If a blob with the same name exists in the linked list, 
        //update the blob by replacing the content (ref or commit) with the given content (ref or commit).

        Blob* same_name = list_find_name(list, name);
        if(same_name != nullptr){
            same_name->ref = ref;

            return same_name;
        }

        //If no blobs with the same name exists in the linked list, 
        //create a new blob with the given content (ref or commit) 
        //and insert it to the linked list with the name following ascending lexicographic order.
        else{
            Blob* newBlob = new Blob;

            newBlob->name = name;
            newBlob->ref = ref;
            newBlob->commit = nullptr;

            int size = list_size(list);

            //if only sentinel node
            if (size == 0){

                Blob* nextBlob = list->head;
                Blob* prevBlob = list->head;

                newBlob->next = nextBlob;
                newBlob->prev = prevBlob;

                prevBlob->next = newBlob;
                nextBlob->prev = newBlob;

                nextBlob = nullptr;
                prevBlob = nullptr;

                return newBlob;
            }

            //if also other nodes
            else if (size >0 ){

                for (Blob* blob = list->head->prev    ; blob != list->head ; blob = blob->prev){
                    if(blob->name <= newBlob->name){
                        //insert it to the linked list with the name following ascending lexicographic order.

                        Blob* nextBlob = blob->next;
                        Blob* prevBlob = blob;

                        newBlob->next = nextBlob;
                        newBlob->prev = prevBlob;

                        prevBlob->next = newBlob;
                        nextBlob->prev = newBlob;

                        nextBlob = nullptr;
                        prevBlob = nullptr;

                        return newBlob;
                        //break;   //写了放心些
                    }
                }
                //if no such blob that (blob->name) <= (newBlob->name),
                //then (newBlob->name) is the smallest one,
                //it should be placed at the beginning.

                Blob* nextBlob = list->head->next;
                Blob* prevBlob = list->head;

                newBlob->next = nextBlob;
                newBlob->prev = prevBlob;

                prevBlob->next = newBlob;
                nextBlob->prev = newBlob;

                nextBlob = nullptr;
                prevBlob = nullptr;

                return newBlob;
            }
            
        }
    }

    return nullptr;  //if (list == nullptr )
}

//debug日志：第一个bug为忘记考虑list为空的情况，和name是最小的的情况//用时约1.5~2h

Blob *list_put(List *list, const string &name, Commit *commit) {

    if(list!=nullptr && commit!=nullptr ){
            
        //If a blob with the same name exists in the linked list, 
        //update the blob by replacing the content (ref or commit) with the given content (ref or commit).

        Blob* same_name = list_find_name(list, name);
        if(same_name != nullptr){
            same_name->commit = commit;

            return same_name;
        }

        //If no blobs with the same name exists in the linked list, 
        //create a new blob with the given content (ref or commit) 
        //and insert it to the linked list with the name following ascending lexicographic order.
        else{
            Blob* newBlob = new Blob;

            newBlob->name = name;
            newBlob->commit = commit;
            newBlob->ref = "";

            int size = list_size(list);

            //if only sentinel node
            if (size == 0){

                Blob* nextBlob = list->head;
                Blob* prevBlob = list->head;

                newBlob->next = nextBlob;
                newBlob->prev = prevBlob;

                prevBlob->next = newBlob;
                nextBlob->prev = newBlob;

                nextBlob = nullptr;
                prevBlob = nullptr;

                return newBlob;
            }

            //if also other nodes
            else if (size >0 ){

                for (Blob* blob = list->head->prev    ; blob != list->head ; blob = blob->prev){
                    if(blob->name <= newBlob->name){
                        //insert it to the linked list with the name following ascending lexicographic order.
                        Blob* nextBlob = blob->next;
                        Blob* prevBlob = blob;

                        newBlob->next = nextBlob;
                        newBlob->prev = prevBlob;

                        prevBlob->next = newBlob;
                        nextBlob->prev = newBlob;

                        nextBlob = nullptr;
                        prevBlob = nullptr;

                        return newBlob;
                        //break;   //写了放心些
                    } 
                }
                //if no such blob that (blob->name) <= (newBlob->name),
                //then (newBlob->name) is the smallest one,
                //it should be placed at the beginning.

                Blob* nextBlob = list->head->next;
                Blob* prevBlob = list->head;

                newBlob->next = nextBlob;
                newBlob->prev = prevBlob;

                prevBlob->next = newBlob;
                nextBlob->prev = newBlob;

                nextBlob = nullptr;
                prevBlob = nullptr;

                return newBlob;
            }

        }
    }
    return nullptr; //if (list == nullptr && commit == nullptr )
}

bool list_remove(List *list, const string &target) {

    if(list!=nullptr){
        //Remove the blob with the target name from the linked list (if found) 
        //and free its memory.
        for (Blob* blob = list->head->next ; blob != list->head ; blob = blob->next )
        {
            if(blob->name == target){

                Blob* nextBlob = blob->next;
                Blob* prevBlob = blob->prev;

                nextBlob->prev = prevBlob;
                prevBlob->next = nextBlob;

                //free its memory.
                delete blob;
                blob = nullptr;

                nextBlob = nullptr;
                prevBlob = nullptr;

                return true;

                break;  //写了放心些
            }
        }
        return false;
    }
    return false;   //if(list == nullptr)
}

int list_size(const List *list) {

    if(list!=nullptr){

        int count;  //The number of blobs in the linked list, excluding the sentinel node.

        for (Blob* blob = list->head->next ; blob != list->head ; blob = blob->next )
        {   count +=1;
        }

        return count;
    }
    return 0;   //if(list == nullptr)
}

void list_clear(List *list) {
    //Remove all blobs from the linked list and free their memory, except the sentinel node. 
    if(list!=nullptr){
        int size = list_size(list);

        string remove_name;
        for (int i = 0; i < size; i++)
        {
            remove_name = list->head->next->name;
            list_remove(list, remove_name);
        }
        //except the sentinel node. 
        //I can't guarantee this, hope this holds
    }

}

// void list_clear(List *list) {
//     //Remove all blobs from the linked list and free their memory, except the sentinel node. 
//     if(list!=nullptr){
//         int size = list_size(list);

//         Blob* deleteBlob = nullptr;
//         for (int i = 0; i < size; i++)
//         {
//             deleteBlob = list->head->next;

//             Blob* nextBlob = deleteBlob->next;
//             Blob* prevBlob = list->head;

//             nextBlob->prev = list->head;
//             prevBlob->next = nextBlob;

//             //free its memory.
//             delete deleteBlob;
//             deleteBlob = nullptr;

//             nextBlob = nullptr;
//             prevBlob = nullptr;

//         }
        
//         //except the sentinel node. 
//         //I can't guarantee this, hope this holds
//     }

// }

void list_delete(List *list) {
    //Delete the linked list and free all associated memory.
    list_clear(list);

    delete list->head;
    list->head = nullptr;

    delete list;
    list = nullptr;

}

void list_replace(List *list, const List *another) {

    if(list!=nullptr && another!=nullptr && list!=another){
        list_clear(list);

        for (Blob* blob = another->head->next ; blob != another->head ; blob = blob->next )
        {   
            //The new copy of the linked list should not share the blobs with the original linked list.
            Blob* newBlob = new Blob;

            newBlob->name = blob->name;
            newBlob->ref = blob->ref;

            //No need to copy commits when copying blobs. (New and existing blob should share the same commit).
            newBlob->commit = blob->commit;

            //maintaining the order of blobs.
            list_push_back(list, newBlob);
        }
    }


}

List *list_copy(const List *list) {

    if(list!=nullptr){
        List* newList = list_new();
        
        for (Blob* blob = list->head->next ; blob != list->head ; blob = blob->next )
        {   
            //The new copy of the linked list should not share the blobs with the original linked list.
            Blob* newBlob = new Blob;

            newBlob->name = blob->name;
            newBlob->ref = blob->ref;

            //No need to copy commits when copying blobs. (New and existing blob should share the same commit).
            newBlob->commit = blob->commit;

            //maintaining the order of blobs.
            list_push_back(newList, newBlob);
        }

        return newList;
    }

    return nullptr;
}//

// Part 2: Gitlite Commands

// Print out the commit info. Used in log.
void commit_print(const Commit *commit) {
    cout << "commit " << commit->commit_id << endl;

    if (commit->second_parent != nullptr) {
        cout << "Merge: " << commit->parent->commit_id.substr(0, 7)
             << " " << commit->second_parent->commit_id.substr(0, 7) << endl;
    }

    cout << "Date: " << commit->time << endl << commit->message;
}

Commit *get_lca(Commit *c1, Commit *c2) {
    return nullptr;
}//
