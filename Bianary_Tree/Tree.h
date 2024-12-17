#pragma once
#include <iostream>
#include <queue>
#include <stack>

// Structure générique pour représenter un nœud d'arbre
template<typename T>
struct Node {
    T data;                  // Contenu du nœud
    struct Node* left;       // Pointeur vers l'enfant gauche
    struct Node* right;      // Pointeur vers l'enfant droit

    // Constructeur pour initialiser un nœud
    Node(T value) : data(value), left(nullptr), right(nullptr) {}
};

// Classe générique pour représenter un arbre binaire
template<typename T>
class Tree
{
private:
    Node<T>* root;            // Racine de l'arbre
    std::queue<Node<T>*> Q;   // File utilisée pour gérer l'insertion

    void deleteTree(Node<T>* node); // Méthode récursive pour libérer la mémoire

public:
    Tree();                   // Constructeur
    void insert(T value);     // Méthode pour insérer une valeur dans l'arbre
    void Affichage_largeur() const;   // Affichage des nœuds par parcours en largeur
    void Affichage_profondeur() const; // Affichage des nœuds par parcours en profondeur
    bool search(T value)const; //recherche
    ~Tree();                  // Destructeur 
};

// Constructeur
template<typename T>
inline Tree<T>::Tree() : root(nullptr) {}

// Méthode d'insertion dans l'arbre
template<typename T>
inline void Tree<T>::insert(T value)
{
    // Crée un nouveau nœud 
    Node<T>* n = new Node<T>(value);

    // Si l'arbre est vide, la nouvelle valeur devient la racine
    if (!root)
    {
        root = n;
        Q.push(n);  // Ajoute le nœud dans la file 
        return;
    }

    // Sinon, insère le nœud dans la première position disponible
    Node<T>* current = Q.front(); // Récupère le premier nœud dans la file

    if (!current->left)
    {
        current->left = n;  // Ajoute le nouveau nœud en tant qu'enfant gauche
    }
    else
    {
        current->right = n; // Ajoute le nouveau nœud en tant qu'enfant droit
        Q.pop();            // Retire le nœud de la file lorsque ses deux enfants sont remplis
    }

    // Ajoute le nouveau nœud dans la file
    Q.push(n);
}

// Méthode pour afficher les nœuds de l'arbre en largeur
template<typename T>
inline void Tree<T>::Affichage_largeur() const
{
    // Si l'arbre est vide
    if (!root)
    {
        return;
    }

    // File temporaire pour gérer l'affichage en largeur
    std::queue<Node<T>*> tempQ;
    tempQ.push(root);  // Ajoute la racine dans la file temporaire

    while (!tempQ.empty())
    {
        // Affiche la valeur du premier nœud dans la file
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

        // Supprime le nœud traité de la file
        tempQ.pop();
    }
    std::cout << std::endl;
}

// Méthode pour afficher les nœuds de l'arbre en profondeur
template<typename T>
inline void Tree<T>::Affichage_profondeur() const
{
    if (!root) return;

    // Pile utilisée pour le parcours en profondeur
    std::stack<Node<T>*> s;
    s.push(root);

    while (!s.empty())
    {
        // Traite le nœud au sommet de la pile
        Node<T>* current = s.top();
        s.pop();

        // Affiche la valeur du nœud
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

// Méthode récursive pour supprimer tous les nœuds
template<typename T>
void Tree<T>::deleteTree(Node<T>* node)
{
    if (!node) return;

    // Supprime d'abord les sous-arbres gauche et droit
    deleteTree(node->left);
    deleteTree(node->right);

    // Supprime le nœud courant
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
    // Supprime tous les nœuds à partir de la racine
    deleteTree(root);
}
