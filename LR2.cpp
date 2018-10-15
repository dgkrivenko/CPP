#include <iostream>
#include <cstdlib>
#include <cstring>
struct elem{
    char* str;
    size_t value;
};
struct node{
    elem data;
    int bal;
    node* left;
    node* right;
    node(elem k) { data = k; left = right = NULL; bal = 0;}
    ~node(){};  
};
node* RightRotation(node* root){
    node* res = root -> left;
    root -> left = res -> right;
    res -> right = root;
    return res; 
}
node* LeftRotation(node* root){
    node* res = root -> right;
    root -> right = res -> left;
    res -> left = root;
    return res;
}
node* Balance(node* root){
    if(root -> bal == -2 && root -> right -> bal == -1){
        root -> bal = 0;
        root -> right -> bal = 0;
        root = LeftRotation(root);
        return root;
    }
    else if(root -> bal == -2 && root -> right -> bal == 0){
        root -> bal = -1;
        root -> right -> bal = 1;
        root = LeftRotation(root);
        return root;
    }
    else if(root -> bal == 2 && root -> left -> bal == 1){
        root -> bal = 0;
        root -> left -> bal = 0;
        root = RightRotation(root);
        return root;
    }
    else if (root -> bal == 2 && root -> left -> bal == 0){
        root -> bal = 1;
        root -> left -> bal = -1;
        root = RightRotation(root);
        return root;
    }
    else if(root -> bal == -2 && root -> right -> bal == 1 && root -> right -> left -> bal == 1){
        root -> bal = 0;
        root -> right -> bal = -1;
        root -> right -> left -> bal = 0;
        root -> right = RightRotation(root -> right);
        root = LeftRotation(root);
        return root;
    }
    else if(root -> bal == -2 && root -> right -> bal == 1 && root -> right -> left -> bal == -1){
        root -> bal = 1;
        root -> right -> bal = 0;
        root -> right -> left -> bal = 0;
        root -> right = RightRotation(root -> right);
        root = LeftRotation(root);
        return root;
    }
    else if (root -> bal == -2 && root -> right -> bal == 1 && root -> right -> left -> bal == 0){
        root -> bal = 0;
        root -> right -> bal = 0;
        root -> right -> left -> bal = 0;
        root -> right = RightRotation(root -> right);
        root = LeftRotation(root);
        return root;
    }
    else if(root -> bal == 2 && root -> left -> bal == -1 && root -> left -> right -> bal == -1){
        root -> bal = 0;
        root -> left -> bal = 1;
        root -> left -> right -> bal = 0;
        root -> left = LeftRotation(root -> left);
        root = RightRotation(root);
        return root;
    }
    else if(root -> bal == 2 && root -> left -> bal == -1 && root -> left -> right -> bal == 1){
        root -> bal = -1;
        root -> left -> bal = 0;
        root -> left -> right -> bal = 0;
        root -> left = LeftRotation(root -> left);
        root = RightRotation(root);
        return root;
    }
    else if (root -> bal == 2 && root -> left -> bal == -1 && root -> left -> right -> bal == 0){
        root -> bal = 0;
        root -> left -> bal = 0;
        root -> left -> right -> bal = 0;
        root -> left = LeftRotation(root -> left);
        root = RightRotation(root);
        return root;
    }
    return NULL;
}
int  Add(node** rootp, elem val){
    int f = 0;
    if(*rootp == NULL){
        *rootp = new node(val);
        std :: cout << "OK" << std :: endl;
    }
    else if (strcasecmp ((*rootp) -> data.str, val.str) < 0) {
        f = Add(&(*rootp) -> right, val);
        if (f == 1) return 1;
        else {
            (*rootp) -> bal--;
            if((*rootp) -> bal == -2 || (*rootp) -> bal == 2){
                (*rootp) = Balance((*rootp));
                if((*rootp) -> bal == 0){
                    return 1;
                }
            }
            if((*rootp) -> bal == 0){
                return 1;
            }
            else return 0;
        }
    }
    else if (strcasecmp((*rootp) -> data.str, val.str) > 0){
        f = Add(&(*rootp) -> left, val);
        if (f == 1) {
            return 1;
        }
        else {
            (*rootp) -> bal++;
            if((*rootp) -> bal == -2 || (*rootp) -> bal == 2){
                (*rootp) = Balance((*rootp));
                if((*rootp) -> bal == 0) {
                    return 1;
                }
            }
            if((*rootp) -> bal == 0){
                return 1;
            }
            else return 0;
        }
    }
    else if (strcasecmp((*rootp) -> data.str, val.str) == 0){
        std :: cout << "Exist" << std :: endl;
        std :: cout << val.str <<std :: endl;
        std :: cout << (*rootp) -> data.str <<std :: endl;
        return 1;
    }
    return 0;
}
node* Find(node** rootp, char val[]){
    if(rootp == NULL || (*rootp) == NULL) {
        return NULL;
    }
    node* buf = (*rootp);
    while( buf != NULL){
        if(strcasecmp(buf -> data.str, val) < 0) {
            buf = buf -> right;
        }
        else if(strcasecmp(buf -> data.str, val) > 0){
            buf = buf -> left;
        }
        else return buf;
    }
    return NULL;
}
node* FindMin(node** rootp){
    node* buf = (*rootp);
    while (buf -> left != NULL){
        buf = buf -> left;
    }
    return buf;
}
int Remove(node** rootp, char val[]){
    int f = 0;
    if(rootp == NULL || (*rootp) == NULL){
        std :: cout << "NoSuchWord" << std :: endl;
        return 1;
    }
    if (strcasecmp((*rootp) -> data.str, val) < 0){
        f = Remove(&(*rootp) -> right, val);
        if (f == 1 || f == -1){
            return 1;
        }
        else {
            (*rootp) -> bal++;
            if((*rootp) -> bal == 2 || (*rootp) -> bal == -2){
                (*rootp) = Balance((*rootp));
            }
            return((*rootp) -> bal);
        }

    }
    else if (strcasecmp((*rootp) -> data.str, val) > 0){
        f = Remove(&(*rootp) -> left, val);
        if (f == 1 || f == -1){
            return 1;
        }
        else {
            (*rootp) -> bal--;
            if((*rootp) -> bal == 2 || (*rootp) -> bal == -2){
                (*rootp) = Balance((*rootp));
            }
            return((*rootp) -> bal);
        }
    }
    if ((*rootp) -> left == NULL){
        node* buf = (*rootp);
        (*rootp) = (*rootp) -> right;
        delete buf; 
        std :: cout << "OK" << std :: endl;
    }
    else if((*rootp) -> right == NULL){
        node* buf = (*rootp);
        (*rootp) = (*rootp) -> left;
        delete buf;
        std :: cout << "OK" << std :: endl;
    }
    else{
        node* buf = FindMin(&(*rootp) -> right);
        (*rootp) -> data = buf -> data;
        f = Remove(&(*rootp) -> right, buf -> data.str);
        if (f == 1 || f == -1){
            return 1;
        }
        else {
            (*rootp) -> bal++;
            if((*rootp) -> bal == 2 || (*rootp) -> bal == -2){
                (*rootp) = Balance((*rootp));
            }
            return((*rootp) -> bal);
        }
    }
    return 0;
}
void Delete(node** rootp){
    if((*rootp) != NULL && (*rootp) -> left != NULL && (*rootp) -> right != NULL){  
        if((*rootp) -> left -> left == NULL && (*rootp) -> left -> right == NULL){
            delete (*rootp) -> left;
            (*rootp) -> left = NULL;
        }
        if((*rootp) -> right -> left == NULL && (*rootp) -> right -> right == NULL){  
            delete (*rootp) -> right;
            (*rootp) -> right = NULL;
        }
    Delete(&((*rootp) -> left));
    Delete(&((*rootp) -> right));
    } 
}
void Serialization(node** rootp, FILE* f){
    int help;
    int notHave = 0;
    int have = 1;
    if((*rootp)){
        if ((*rootp) -> left == NULL){
            fwrite(&notHave, sizeof(int), 1, f);
        }
        else {
            fwrite(&have, sizeof(int), 1, f);
        }
        if((*rootp) -> right == NULL){
            fwrite(&notHave, sizeof(int), 1, f);
        }
        else{
            fwrite(&have, sizeof(int), 1, f);
        }
        help = strlen((*rootp) -> data.str);
        fwrite(&help, sizeof(int), 1, f);
        fwrite((*rootp) -> data.str, sizeof(char), strlen((*rootp) -> data.str), f);
        fwrite(&(*rootp) -> data.value, sizeof(size_t), 1, f);
        help = (*rootp) -> bal;
        fwrite(&help, sizeof(int), 1, f);
        if((*rootp) -> right == NULL && (*rootp) -> left == NULL)return;
        Serialization(&(*rootp) -> left, f);
        Serialization(&(*rootp) -> right, f);
    }
    return;
}
node* Deserialisation(FILE* f){
    int flagLeft;
    int flagRight;
    int size;
    elem ob;
    fread(&flagLeft, sizeof(int), 1, f);
    fread(&flagRight, sizeof(int), 1, f);
    fread(&size, sizeof(int), 1, f);
    ob.str = new char[size + 4];
    fread(ob.str, sizeof(char), size, f);
    fread(&ob.value, sizeof(size_t), 1, f);
    node* buf = new node(ob);
    fread(&buf -> bal, sizeof(int), 1, f);
    if (flagLeft == 1){
        buf -> left = Deserialisation(f);
    }
    if(flagRight == 1){
        buf -> right = Deserialisation(f);
    }
    if(flagLeft == 0 && flagRight == 0){
        return buf;
    }
    return buf;
}
int main(){
    elem ob;
    char action;
    char buf[260];
    char path[260];
    node* root = NULL;
    node* help;
    while (std :: cin >> action){
        if(action == '+'){
            std :: cin >> buf;
            ob.str = new char[strlen(buf) + 1];
            strcpy(ob.str, buf);
            std :: cin >> ob.value;
            Add(&root, ob);
        }
        else if (action == '-'){
            std :: cin >> buf;
            Remove (&root, buf);
        }
        else if(action == '!'){
            std :: cin >> buf;
            if(strcmp (buf, "Save") == 0){
                std :: cin >> path;
                FILE* f = fopen(path, "wb");
                if (f == NULL){
                    std :: cout << "ERROR: Couldn't create file" << std :: endl;
                }
                else {
                    Serialization(&root, f);
                    std :: cout << "OK" << std :: endl;
                    fclose(f);
                }
            }
            else if(strcmp(buf, "Load") == 0){
                std :: cin >> path;
                FILE* f = fopen(path, "rb");
                if(f == NULL){
                    std :: cout << "ERROR: Couldn't create file" << std :: endl;
                }
                else {
                    Delete(&root);
                    root = Deserialisation(f);
                    std :: cout << "OK" << std :: endl;
                    fclose(f);
                }
            }
        }
        else {
            ungetc(action, stdin);
            std :: cin >> buf;
            help = Find(&root, buf);
            if (help == NULL)std :: cout << "NoSuchWord" << std :: endl;
            else std :: cout << "OK: " << help -> data.value << std :: endl;
        }
    }
    Delete (&root);
    return 0;
}
