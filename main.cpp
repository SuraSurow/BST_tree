#include <iostream>
#include <random>
#include <ctime>

using namespace std;

unsigned int randValue(unsigned int max) {
    std::random_device rd; // Inicjalizacja generatora losowego na podstawie sprzÄ™tu
    std::mt19937 gen(rd()); // Mersenne Twister engine

    std::uniform_int_distribution<unsigned int> dist(0, max);

    return dist(gen);
}
char randChar()
{

    char ret = 65 + (rand() % 25);
    return  ret;
}

struct Osoba
{
    unsigned int wiek;
    char imie;
    Osoba()
    {
        wiek = 1;
        imie = '0';
    }
    Osoba(unsigned int age , char name)
    {
        wiek = age;
        imie = name;
    }
    Osoba(unsigned int age )
    {
        wiek = age;
        imie=randChar();
    }
    Osoba(char name )
    {
        imie = name;
        wiek = randValue(1000);
    }
    void updateData(const Osoba& objInp)
    {
        wiek = objInp.wiek;
        imie = objInp.imie;
    }


};



int indexGlow;

template<typename T>
struct Node_BST
{
    Node_BST<T> *left , *right , *father;
    T data;
    int index;
    Node_BST():left(nullptr),right(nullptr),father(nullptr),data(nullptr),index(0)
    {
        index = indexGlow++;
    }
    Node_BST(T obj):left(nullptr),right(nullptr),father(nullptr),data(obj),index(0)
    {
        index = indexGlow++;
    }
    ~Node_BST()
    {
        left = nullptr;
        right = nullptr;
        father = nullptr;
        delete data;
    }



};

int compInt(Osoba* left , Osoba* right)
{
    if(left->wiek > right->wiek) return 1;
    else if( left->wiek < right->wiek) return -1;
    else return 0;
}
char compChar(Osoba* left , Osoba* right)
{
    if(left->imie > right->imie) return 1;
    else if( left->imie < right->imie) return -1;
    else return 0;
}

template<typename T>
struct BST_tree {
    Node_BST<T> *root;
    int size;

    BST_tree ( ) {
        root = nullptr;
        size = 0;
    }

    void printOsoba ( Osoba * obj)
    {
        if(obj == nullptr)
        {
            cout<<" brak";
            return;
        }
        cout<<obj->wiek;
    }



    bool add ( Node_BST<T> *rootInp, T obj ) {
        if ( rootInp == nullptr ) {
            root = new Node_BST<T>();
            root->data = obj;
            size++;
            return true;
        }
            /*
             else if ( findNode(rootInp,obj) != nullptr) {
                 return false;
             }
             */
        else if ( compInt(rootInp->data, obj) == 1 )//idziemy na lewo
        {
            if ( rootInp->left == nullptr ) {
                Node_BST<T> *newNode = new Node_BST<T>();
                newNode->data = obj;
                newNode->father = rootInp;
                rootInp->left = newNode;
                size++;
                return true;
            } else {
                return add(rootInp->left, obj);
            }
        } else if ( compInt(rootInp->data, obj) == -1 )//idziemy na prawo
        {

            if ( rootInp->right == nullptr ) {
                Node_BST<T> *newNode = new Node_BST<T>();
                newNode->data = obj;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                newNode->father = rootInp;
                rootInp->right = newNode;
                size++;
                return true;
            } else {
                return add(rootInp->right, obj);
            }
        } else {
            return false;
        }
    }


    Node_BST<T> *findNode ( Node_BST<T>* rootInp, T obj ) {
        if ( rootInp == nullptr ) {
            return nullptr;
        }
        int comparison = compInt(rootInp->data, obj);
        if ( comparison == 1 )//idziemy na lewo
        {
            return findNode( rootInp->left, obj);
        } else if ( comparison == -1 )//idziemy na prawo
        {
            return findNode( rootInp->right, obj);
        } else {
            return rootInp;
        }
    }

    T findObj ( Node_BST<T> *rootInp, T obj ) {
        if ( rootInp == nullptr ) {
            return nullptr;
        }
        int comparison = compInt(rootInp->data, obj);
        if ( comparison == 1 )//idziemy na lewo
        {
            return findObj(rootInp->left, obj);
        } else if ( comparison == -1 )//idziemy na prawo
        {
            return findObj(rootInp->right, obj);
        } else {
            return rootInp->data;
        }
    }

    T findObj ( Node_BST<T> *rootInp, int index ) {
        if ( rootInp == nullptr ) {
            return nullptr;
        }
        int comparison = compInt(rootInp->index, index);
        if ( comparison == 1 )//idziemy na lewo
        {
            return findObj(rootInp->left, index);
        } else if ( comparison == -1 )//idziemy na prawo
        {
            return findObj(rootInp->right, index);
        } else {
            return rootInp->data;
        }
    }


    T findMinObj ( Node_BST<T> *rootInp ) {
        if ( rootInp == nullptr ) {
            return nullptr;
        }
        if ( rootInp->left == nullptr ) {
            return rootInp->data;
        }
        return findMinObj(rootInp->left);
    }

    T findMaxObj ( Node_BST<T> *rootInp ) {
        if ( rootInp == nullptr ) {
            return nullptr;
        }
        if ( rootInp->right == nullptr ) {
            return rootInp->data;
        }
        return findMaxObj(rootInp->right);
    }

    Node_BST<T> *findMinNode ( Node_BST<T> *rootInp ) {
        if ( rootInp == nullptr ) {
            return nullptr;
        }
        if ( rootInp->left == nullptr ) {
            return rootInp;
        }
        return findMinNode(rootInp->left);
    }

    Node_BST<T> *findMaxNode ( Node_BST<T> *rootInp ) {
        if ( rootInp == nullptr ) {
            return nullptr;
        }
        if ( rootInp->right == nullptr ) {
            return rootInp;
        }
        return findMaxNode(rootInp->right);
    }

    void preOrderTraversal(Node_BST<T>* rootInp) {
        if (rootInp == nullptr) {
            return;
        }
        cout<<"\nObj: ";
        printOsoba(rootInp->data);
        cout<<"  Father= ";
        if(rootInp->father != nullptr)printOsoba( rootInp->father->data );
        else cout<<"- ";
        cout<<"  L.Child= ";
        if(rootInp->left != nullptr)printOsoba( rootInp->left->data );
        else cout<<"- ";
        cout<<"  P.Child= ";
        if(rootInp->right != nullptr)printOsoba( rootInp->right->data );
        else cout<<"- ";
        preOrderTraversal(rootInp->left);
        preOrderTraversal(rootInp->right);
    }

    void inOrderTraversal(Node_BST<T>* rootInp) {
        if (rootInp == nullptr) {
            return;
        }
        inOrderTraversal(rootInp->left);
        printOsoba(rootInp->data);
        inOrderTraversal(rootInp->right);
    }


    bool deleteObj ( Node_BST<T> *rootInp, T obj ) {
        if ( findObj( rootInp, obj)  == nullptr) return false;//sprawdza czy obiekt do usuniecia istnieje
        return deleteNode(findNode( rootInp, obj));
    }


    bool deleteNode(Node_BST<T> *delNode) {
        if (delNode == nullptr) {
            return false;
        } else if (delNode->left == nullptr && delNode->right == nullptr) {
            if (delNode->father == nullptr) {
                root = nullptr;
            } else if (delNode->father->left == delNode) {
                delNode->father->left = nullptr;
            } else {
                delNode->father->right = nullptr;
            }
            delete delNode;
            size--;
            return true;
        } else if (delNode->right == nullptr) {
            Node_BST<T> *child = delNode->left;
            if (delNode->father == nullptr) {
                root = child;
                child->father = nullptr;
            } else if (delNode->father->left == delNode) {
                delNode->father->left = child;
                child->father = delNode->father;
            } else {
                delNode->father->right = child;
                child->father = delNode->father;
            }
            delete delNode;
            size--;
            return true;
        } else if (delNode->left == nullptr) {
            Node_BST<T> *child = delNode->right;
            if (delNode->father == nullptr) {
                root = child;
                child->father = nullptr;
            } else if (delNode->father->left == delNode) {
                delNode->father->left = child;
                child->father = delNode->father;
            } else {
                delNode->father->right = child;
                child->father = delNode->father;
            }
            delete delNode;
            size--;
            return true;
        } else {
            Node_BST<T> *successor = findMinNode(delNode->right);
            T ptr = delNode->data;
            delNode->data = successor->data;
            successor->data = ptr;
            delNode->index = successor->index;

            // Usuń successor
            if (successor->father->left == successor) {
                successor->father->left = successor->right;
            } else {
                successor->father->right = successor->right;
            }
            if (successor->right) {
                successor->right->father = successor->father;
            }
            delete successor;
            size--;

            return true;
        }
    }



    void deleteTree(Node_BST<T>* rootInp) {
        if ( rootInp == nullptr ) {
            return;
        }
        deleteTree(rootInp->left);
        deleteTree(rootInp->right);
        size--;
        delete rootInp;
    }

    int getHeight(Node_BST<T>* rootInp) {
        if (rootInp == nullptr) {
            return 0;
        }
        int leftHeight = getHeight(rootInp->left);
        int rightHeight = getHeight(rootInp->right);
        return std::max(leftHeight, rightHeight) + 1;
    }




};


int main()
{
    srand(time(nullptr));

    /*
    BST_tree<Osoba*> *drzewo = new BST_tree<Osoba*>();

    clock_t startAdd = clock();

    int powtWartosciDodawanej = 0;
    for (int i = 0; i < 10; i++) {
        Osoba *obj = new Osoba(randValue(100), randChar());
        if (!drzewo->add(drzewo->root, obj)) powtWartosciDodawanej++;
        int w = drzewo->getHeight(drzewo->root);
        cout<<"\nIlosc warst  drzewa "<<drzewo->getHeight(drzewo->root);
    }
    clock_t endAdd = clock();
    double timeTakenAdd = double(endAdd - startAdd) / CLOCKS_PER_SEC;
    std::cout << "Czas dodawania: " << timeTakenAdd << " sekund" << std::endl;
    cout<<"\nwielkosc drzewa "<<drzewo->size;

    drzewo->inOrderTraversal(drzewo->root);


    clock_t startDelete = clock();
    drzewo->deleteTree(drzewo->root);
    cout<<"\nwielkosc drzewa "<<drzewo->size;
    clock_t endDelete = clock();
    double timeTakenDelete = double(endDelete - startDelete) / CLOCKS_PER_SEC;
    std::cout << "Czas usuwania: " << timeTakenDelete << " sekund" << std::endl;

    delete drzewo;

   */



    BST_tree<Osoba*> *drzewoDwa = new  BST_tree<Osoba*>();
    Osoba* obj1 = new Osoba(5,randChar());
    Osoba* obj2 = new Osoba(2,randChar());
    Osoba* obj3 = new Osoba(8,randChar());
    Osoba* obj4 = new Osoba(1,randChar());
    Osoba* obj5 = new Osoba(4,randChar());
    Osoba* obj6 = new Osoba(6,randChar());
    Osoba* obj7 = new Osoba(9,randChar());

    drzewoDwa->add(drzewoDwa->root,obj1);

    drzewoDwa->add(drzewoDwa->root,obj2);

    drzewoDwa->add(drzewoDwa->root,obj3);

    drzewoDwa->add(drzewoDwa->root,obj4);

    drzewoDwa->add(drzewoDwa->root,obj5);

    drzewoDwa->add(drzewoDwa->root,obj6);

    drzewoDwa->add(drzewoDwa->root,obj7);

    drzewoDwa->preOrderTraversal(drzewoDwa->root);


    cout<<"\na\n";
    drzewoDwa->deleteObj( drzewoDwa->root , obj1
    );

    drzewoDwa->preOrderTraversal(drzewoDwa->root);

    return 666;





    /*

     */



}


