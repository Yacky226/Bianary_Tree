#pragma once
#include <iostream>
#include <queue>
#include <stack>

// Structure g�n�rique pour repr�senter un n�ud d'arbre
template<typename T>
struct Node {
    T data;                  // Contenu du n�ud
    struct Node* left;       // Pointeur vers l'enfant gauche
    struct Node* right;      // Pointeur vers l'enfant droit

    // Constructeur pour initialiser un n�ud
    Node(T value) : data(value), left(nullptr), right(nullptr) {}
};

// Classe g�n�rique pour repr�senter un arbre binaire
template<typename T>
class Tree
{
private:
    Node<T>* root;            // Racine de l'arbre
    std::queue<Node<T>*> Q;   // File utilis�e pour g�rer l'insertion

    void deleteTree(Node<T>* node); // M�thode r�cursive pour lib�rer la m�moire

public:
    Tree();                   // Constructeur
    void insert(T value);     // M�thode pour ins�rer une valeur dans l'arbre
    void Affichage_largeur() const;   // Affichage des n�uds par parcours en largeur
    void Affichage_profondeur() const; // Affichage des n�uds par parcours en profondeur
    bool search(T value)const; //recherche
    ~Tree();                  // Destructeur 
};

// Constructeur
template<typename T>
inline Tree<T>::Tree() : root(nullptr) {}

// M�thode d'insertion dans l'arbre
template<typename T>
inline void Tree<T>::insert(T value)
{
    // Cr�e un nouveau n�ud 
    Node<T>* n = new Node<T>(value);

    // Si l'arbre est vide, la nouvelle valeur devient la racine
    if (!root)
    {
        root = n;
        Q.push(n);  // Ajoute le n�ud dans la file 
        return;
    }

    // Sinon, ins�re le n�ud dans la premi�re position disponible
    Node<T>* current = Q.front(); // R�cup�re le premier n�ud dans la file

    if (!current->left)
    {
        current->left = n;  // Ajoute le nouveau n�ud en tant qu'enfant gauche
    }
    else
    {
        current->right = n; // Ajoute le nouveau n�ud en tant qu'enfant droit
        Q.pop();            // Retire le n�ud de la file lorsque ses deux enfants sont remplis
    }

    // Ajoute le nouveau n�ud dans la file
    Q.push(n);
}

// M�thode pour afficher les n�uds de l'arbre en largeur
template<typename T>
inline void Tree<T>::Affichage_largeur() const
{
    // Si l'arbre est vide
    if (!root)
    {
        return;
    }

    // File temporaire pour g�rer l'affichage en largeur
    std::queue<Node<T>*> tempQ;
    tempQ.push(root);  // Ajoute la racine dans la file temporaire

    while (!tempQ.empty())
    {
        // Affiche la valeur du premier n�ud dans la file
        Node<T>* current = tempQ.front();
        std::cout << current->data << " ";

        // Ajoute l'enfant gauche dans la file si existant
        if (current->left)
        {
            tempQ.push(current->left);
        }

        // Ajoute l'enfant droit dans la file si existant
        if (current->right)
        {
            tempQ.push(current->right);
        }

        // Supprime le n�ud trait� de la file
        tempQ.pop();
    }
    std::cout << std::endl;
}

// M�thode pour afficher les n�uds de l'arbre en profondeur
template<typename T>
inline void Tree<T>::Affichage_profondeur() const
{
    if (!root) return;

    // Pile utilis�e pour le parcours en profondeur
    std::stack<Node<T>*> s;
    s.push(root);

    while (!s.empty())
    {
        // Traite le n�ud au sommet de la pile
        Node<T>* current = s.top();
        s.pop();

        // Affiche la valeur du n�ud
        std::cout << current->data << " ";

        // Empile les enfants 
        if (current->right)
        {
            s.push(current->right);
        }
        if (current->left)
        {
            s.push(current->left);
        }
    }
    std::cout << std::endl;
}

// M�thode r�cursive pour supprimer tous les n�uds
template<typename T>
void Tree<T>::deleteTree(Node<T>* node)
{
    if (!node) return;

    // Supprime d'abord les sous-arbres gauche et droit
    deleteTree(node->left);
    deleteTree(node->right);

    // Supprime le n�ud courant
    delete node;
}

template<typename T>
inline bool Tree<T>::search(T value) const
{
    if(!root)
    return false;
    std::queue<Node<T>*> tempQ;

    tempQ.push(root);
    while (!tempQ.empty())
    {
        if (tempQ.front()->data == value)
        {
            return true;
        }
        if (tempQ.front()->left) {
            tempQ.push(tempQ.front()->left);
        }
        if (tempQ.front()->right) {
            tempQ.push(tempQ.front()->right);
        }
        tempQ.pop();
        
    }
    return false;
}

// Destructeur
template<typename T>
inline Tree<T>::~Tree()
{
    // Supprime tous les n�uds � partir de la racine
    deleteTree(root);
}
