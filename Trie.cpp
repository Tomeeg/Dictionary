#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

#define ALPHABET_SIZE  26

struct TrieNode
{
	TrieNode *children[ALPHABET_SIZE];
	bool isEndOfWord;
	string translation;
};

TrieNode* getNode()
{
	TrieNode* pNode = new TrieNode;

	pNode->isEndOfWord = false;

	for (int i = 0; i < ALPHABET_SIZE; i++)
		pNode->children[i] = NULL;

	return pNode;
}

void insert(TrieNode* root, string key, string translation)
{
	TrieNode* node = root;

	for (int i = 0; i < key.length(); i++)
	{
		int index = key[i] - 'a';
		if (!node->children[index])
			node->children[index] = getNode();

		node = node->children[index];
	}

	node->isEndOfWord = true;
	node->translation = translation;
}

void printAllChildren(TrieNode* node)
{
	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		if (node->children[i] != NULL && node->children[i]->isEndOfWord)
			cout << node->children[i]->translation << endl;
		if (node->children[i] != NULL)
			printAllChildren(node->children[i]);
	}
}

void searchByPrefix(TrieNode* root, string key)
{
	TrieNode* node = root;
	for (int i = 0; i < key.length(); i++)
	{
		int index = key[i] - 'a';
		if (!node->children[index])
		{
			cout << "-" << endl;
			return;
		}
		node = node->children[index];
	}
	if (node != NULL && node->isEndOfWord)
		cout << node->translation << endl;
	if (node != NULL)
		printAllChildren(node);
}

string search(TrieNode* root, string key)
{
	TrieNode* node = root;

	for (int i = 0; i < key.length(); i++)
	{
		int index = key[i] - 'a';
		if (!node->children[index])
			return "-";

		node = node->children[index];
	}

	if (node != NULL && node->isEndOfWord)
		return node->translation;
	else return "-";
}

int main()
{
	string word, trans;
	char c;
	TrieNode* root = getNode();

	while (cin >> c)
	{
		switch (c)
		{
		case '+':
			cin >> word >> trans;
			insert(root, word, trans);
			break;
		case '?':
			cin >> word;
			cout << search(root, word) << endl;
			break;
		case '*':
			cin >> word;
			searchByPrefix(root, word);
			break;
		}
	}
	delete root;
	return 0;
}