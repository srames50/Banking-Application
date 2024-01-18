#ifndef BSTREE_H
#define BSTREE_H

#include "Account.h"

class BinarySearchTree{

	struct Node{
		Account* p_account;
		Node* right;
		Node* left;
	};

	friend ostream& operator<<(ostream stream, BinarySearchTree& rhs);

	public:
		BinarySearchTree();
		BinarySearchTree(const BinarySearchTree& bst);
		~BinarySearchTree();

		bool Delete(const int& account_id, Account* & account);
		bool DeleteHelper(int& acct_num, Account*& account, Node* root);
		bool IsEmpty() const;
		
		bool Retrieve(const int& acct_number, Account*& account) const;
		bool RetrieveHelper(int acct_num, Account*& p_account, Node* root) const;
		bool Insert(Account* account);
		void Display() const;
		void DisplayHelper(Node* root) const;
		bool InsertHelper(Account* p_account, Node*& root);
		int Size() const;
		Account* Find(int acct_num);
		Account* FindHelper(int acct_num, Node*& root);


		BinarySearchTree operator=(const BinarySearchTree& rhs);

	private:
		Node* root_;
		
};

#endif