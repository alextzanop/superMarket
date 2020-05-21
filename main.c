//18:05 last edit
/*************************************************************
 * @file   main.c                                            *
 * @author Papaioannou Antonis 						  	     *
 *                                                    	     *
 * @brief  Source file for the needs of CS-240b project 2018 *
 ************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "Shopping.h"

#define BUFFER_SIZE 1024  /* Maximum length of a line in input file */

/* Uncomment the following line to enable debugging prints 
 * or comment to disable it */
#define DEBUG

#ifdef DEBUG
#define DPRINT(...) fprintf(stderr, __VA_ARGS__);
#else  /* DEBUG */
#define DPRINT(...)
#endif /* DEBUG */

//Signatures

/**
 * @brief Print shops
 *
 * @return 1 on success
 *         0 on failure
 */
int PrintShops (void);

/**
 * @brief Print customers
 *
 * @return 1 on success
 *         0 on failure
 */
int PrintCustomers (void);


/**
 *@brief Creates a new Shop 
 *
 *@param sid The shop's ID
 *@param type The shop's type
 *
 *@return a new Shop
 */
struct Shop* makeNewShop(int sid, int type);
/**
 *@brief prints all Shops
 *
 *@param root of the shops tree
 *@param products marks if this function should print the shop's products
 */
void ShopPrint(struct Shop* root, int products );

/**
 *@brief finds a shop in the shop tree
 *
 *@param sid the shop's id
 *
 *@return the Shop if found, the shopSentinel otherwise
 *
 */
struct Shop* findShop(int sid);
/**
 *@brief creates a new shop Product
 *
 *@param sid  the product's id
 *@param quantity the products's quantity
 *@param price the product's price
 *
 *@return the new shop Product
 */
struct Product* makeNewProd(int pid, int quantity, int price);

/**
 *@brief print all shops' products
 */
void PrintProducts(void);

/**
 *@brief Prints the products of a specific Shop
 *
 *@param a Shop
 */
void PrintShopProducts(struct Shop* shop);

/**
 *@brief initializes the customer hash table
 *
 *@return the initialized hash table
 *
 */
struct Customer** initHash();

/**
 *@brief calculates the desirable hash table size
 *
 *@return the hash table size
 *
 */
int selectTableSize();

/**
 *@brief creates the customer hash table
 *
 *@return the customer hash table
 *
 */
struct Customer** makeHashTable();

/**
 *@brief the first hash function
 *
 *@param cid a customer's id
 *@param mod a prime number
 *
 *@return the hash key
 */
int hashFunc1(int cid, int mod);

/**
 *@brief the second hash function
 *
 *@param cid a customer's id
 *@param mod a prime number
 *
 *@return the hash key
 */
int hashFunc2(int cid, int mod);

/**
 *@brief calculates a customer's hash table index
 *
 *@param cid the customer's id
 *@param N a prime number
 *
 *@return the customer's hash index
 */
int customerIndex(int cid, int N);

/**
 *@brief creates a new custmoer
 *
 *@param cid the customer's id
 *
 *@return the new customer
 */
struct Customer* makeCustomer(int cid);

/**
 *@brief select a prime number for the second hash function depending on the hash table size
 *
 *@return a prime number
 */
int selectSecondPrime();

/**
 *@brief creates a new C_Product
 *
 *@param pid the product's id
 *@param quantity the product's quantity
 *
 *@return the new 
 */
struct C_Product* makeCProd(int pid, int quantity);

/**
 *@brief Finds a customer in the hash table
 *
 *@param cid the customer's id
 *
 *@return the Customer if found, null otherwise
 */
struct Customer* findCustomerInTable(int cid);

/**
 *@brief initializes the customer tree
 *
 *@return the root of the new tree
 */
struct C_Product* initCustTree();

/**
 *@brief adds a new product to the customer tree
 *
 *@param tree the tree's root
 *@param product the product to add
 *
 *@return the root of the tree
 */
struct C_Product* addToCustTree(struct C_Product* tree, struct C_Product* product);

/**
 *@brief prints all the products for all the customers
 */
void printAllCProducts();

/**
 *@brief prints the products of a single customer
 *
 *@param root the customer tree's root
 */
void printCProducts(struct C_Product* root);

/**
 *@brief removes a product from a customer's tree
 *
 *@param root the customer's tree root
 *@param pid the product's id
 *
 *@return the tree's root
 */
struct C_Product* removeFromCustomerTree(struct C_Product* root ,int pid);

/**
 *@brief finds the product with the lowest pid of a tree
 *
 *@param product the root of the tree
 *
 *@return NULL if the tree is empty, the min product otherwise
 *
 */
struct C_Product* minProduct(struct C_Product* product);

/**
 *@brief transforms a tree to an array
 *
 *@param tree a tree
 *@param table the array to store the tree
 *@param start the position in which to add a product in the table
 *
 */
void treeToTable(struct C_Product* tree, struct C_Product** table, int* start);

/**
 *@brief prints the contents of a table
 *
 *@param table the table which to print
 *@param size the size of the table
 */
void printTable(struct C_Product** table, int size);

/**
 *@brief buys the products of a customer from the shops
 *
 *@param shop the shop from which to buy
 *@param customer the customer who's buying the products
 *@param table a table with the customer's products
 */
void buyProducts(struct Shop* shop, struct Customer* customer, struct C_Product** table);

/**
 *@brief removes a product from a shop
 *
 *@param shop the shop from whih to remove a product
 *@param prod the product to remove
 *@param prev the the product that comes before prod
 *
 *@return the prev product if prod != prev, the new head of the list otherwise
 */
struct Product* removeShopProduct(struct Shop* shop, struct Product* prod, struct Product* prev);

/**
 *@brief searches a shop for the customer's products
 *
 *@param shop shop to search
 *@param customer the customer which buys from the shop
 *@param table a table with the customer's products
 */
void searchShop(struct Shop* shop, struct Customer* customer, struct C_Product** table);

/**
 *@brief updates a customer's product tree
 *
 *@param customer the customer whose tree to update
 *@param tableProd a customer product in the table
 *
 *@return the new customer shopping tree size
 */
int updateCustomerTree(struct Customer* customer, struct C_Product* tableProd);

/**
 *@brief finds a product in a customer's tree
 *
 *@param root the root of the customer's tree
 *@param prod the product to find
 *
 *@return the product if found, NULL otherwise
 */
struct C_Product* findInCustTree(struct C_Product* root, struct C_Product* prod);

/**
 *@brief prints a customer's products
 *
 *@param customer the customer whose products to print
 */
void printCustomer(struct Customer* customer);

/**
 *@brief merges two tables to one
 *
 *@param mergedTable the merged table
 *@param table1 a table to merge
 *@param table2 a table to merge
 *@param size1 table1's size
 *@param size2 table2's ize
 *
 *@return the size of the merged table
 */
int mergeTables(struct C_Product** mergedTable, struct C_Product** table1, struct C_Product** table2, int size1, int size2);

/**
 *@brief transform a table to a binary tree
 *
 *@param table the table to turn into a tree
 *@param start the start of the rable
 *@param end the end of the table
 *
 *@return the root of the tree created
 */
struct C_Product* tableToTree(struct C_Product** table, int start, int end);


/**
 *@brief gets the first digit of an integer
 *
 *@param N an integer
 *
 *@return N's first digit
 */
int getFirstDigit(int N);

/**
 *
 *
 *
 *
 */
void printCategories(){

	int i ;
	for(i=0;i<5;i++){
		if(ShopTypes[i]){
			printf("\nCategory_%d: \n",i+1);
			ShopPrint(ShopTypes[i],0);
		}
	}
}

//Helper functions

/**
 *@brief Creates a new Shop 
 *
 *@param sid The shop's ID
 *@param type The shop's type
 *
 *@return a new Shop
 */
struct Shop* makeNewShop(int sid, int type){

	struct Shop* newShop = malloc(sizeof(struct Shop));
	newShop->sid = sid;
	newShop->type = type;
	newShop->products = NULL;
	newShop->lc = shopSentinel;
	newShop->rc = shopSentinel;
	
	return newShop;
}

/**
 *@brief prints all Shops
 *
 *@param root of the shops tree
 *@param products marks if this function should print the shop's products
 */
void ShopPrint(struct Shop* root, int products ){
	fflush(stdout);
	if(root==shopSentinel||!root)
		return;
	ShopPrint(root->lc,products);
	if(products)
		printf("\nShop");
	printf("<%d, %d>",root->sid,root->type);
	
	if(products){
		PrintShopProducts(root);
		printf("\n");
	}
	else{
		if(root->rc!=shopSentinel)
			printf(",");
		printf(" ");
	}
	ShopPrint(root->rc, products);
	
	
	

}

/**
 *@brief finds a shop in the shop tree
 *
 *@param sid the shop's id
 *
 *@return the Shop if found, the shopSentinel otherwise
 *
 */
struct Shop* findShop(int sid){

	struct Shop* iterShop = shopRoot;
	
	while(iterShop!=shopSentinel){
	
		if(iterShop->sid==sid)
			return iterShop;
		if(iterShop->sid>sid)
			iterShop = iterShop->lc;
		else
			iterShop = iterShop->rc;
		
	}
	return iterShop;
	
}

/**
 *@brief creates a new shop Product
 *
 *@param sid  the product's id
 *@param quantity the products's quantity
 *@param price the product's price
 *
 *@return the new shop Product
 */
struct Product* makeNewProd(int pid, int quantity, int price){
	struct Product*	newProd = malloc(sizeof(struct Product));
	newProd->pid = pid;
	newProd->qty = quantity;
	newProd->price = price;
	newProd->next = NULL;
	return newProd;
	
}

/**
 *@brief print all shops' products
 */
void PrintProducts(void){
	
	ShopPrint(shopRoot, 1);
}

/**
 *@brief Prints the products of a specific Shop
 *
 *@param a Shop
 */
void PrintShopProducts(struct Shop* shop){
	assert(shop!=NULL);
	
	fflush(stdout);
	struct Product* iter = shop->products;
	while(iter){
		printf("\n  Products: ");
		printf("<%d, %d, %d>",iter->pid, iter->qty, iter->price);
		if(iter->next)
			printf(", ");
		iter = iter->next;	
	}
	printf("\n");
	
}

/**
 *@brief initializes the customer hash table
 *
 *@return the initialized hash table
 *
 */
struct Customer** initHash(){
	if(!customers_hash){
		//init customer hash table
		customers_hash = malloc(sizeof(struct Customer*)*max_customers_g);
		int tabSize = selectTableSize();
		
		int i;
		for(i=0; i<tabSize; i++){
			customers_hash[i]=NULL;
			
		}
		
	}
	return customers_hash;
}

/**
 *@brief calculates the desirable hash table size
 *
 *@return the hash table size
 *
 */
int selectTableSize(){
	int tableSize = 0;
	int i=0;
	while(tableSize<max_customers_g)
		tableSize=primes_g[i++];
	return tableSize;
}

/**
 *@brief creates the customer hash table
 *
 *@return the customer hash table
 *
 */
struct Customer** makeHashTable(){
	customers_hash = malloc(selectTableSize()*sizeof(struct Customer*));
	return customers_hash;
}

/**
 *@brief the first hash function
 *
 *@param cid a customer's id
 *@param mod a prime number
 *
 *@return the hash key
 */
int hashFunc1(int cid, int mod){
	return cid%mod;
}

/**
 *@brief the second hash function
 *
 *@param cid a customer's id
 *@param mod a prime number
 *
 *@return the hash key
 */
int hashFunc2(int cid, int mod){
	return (mod-(cid%mod))%mod;
}

/**
 *@brief calculates a customer's hash table index
 *
 *@param cid the customer's id
 *@param N a prime number
 *
 *@return the customer's hash index
 */
int customerIndex(int cid, int N){
	int delta = 0;	
	int k = 0;
	int pos = 0;
	int prime = 1;
	
	pos = hashFunc1(cid, N);
	//go to second hash
	
	if(customers_hash[pos]){
		prime = selectSecondPrime();
		
		delta = hashFunc2(cid, prime)%N;
		//delta = 0
		if(!delta)
			delta = 1;
		
		do{
			k++;
			pos = (hashFunc1(cid, N) + k*delta)%N;
			
		}while(customers_hash[pos]);
			
			
			
			
	}
	return pos;
	
}

/**
 *@brief creates a new custmoer
 *
 *@param cid the customer's id
 *
 *@return the new customer
 */
struct Customer* makeCustomer(int cid){
	struct Customer* newCustomer = malloc(sizeof(struct Customer));
	newCustomer->cid = cid;
	newCustomer->shopping_size = 0;
	newCustomer->shopping_tree = NULL;
	
	return newCustomer;
	
}

/**
 *@brief select a prime number for the second hash function depending on the hash table size
 *
 *@return a prime number
 */
int selectSecondPrime(){
	int prime = 1;
	int prev = 1;
	int index = 0;
	int size = selectTableSize();
	while(prime<size){
		prev = prime;
		prime = primes_g[index++];
	}
	return prev;
}

/**
 *@brief creates a new C_Product
 *
 *@param pid the product's id
 *@param quantity the product's quantity
 *
 *@return the new 
 */
struct C_Product* makeCProd(int pid, int quantity){
	struct C_Product* newProd = malloc(sizeof(struct C_Product));
	newProd->pid = pid;
	newProd->qty = quantity;
	newProd->lc = NULL;
	newProd->rc = NULL;
	
	return newProd;
	
}

/**
 *@brief Finds a customer in the hash table
 *
 *@param cid the customer's id
 *
 *@return the Customer if found, null otherwise
 */
struct Customer* findCustomerInTable(int cid){
	int size = selectTableSize();
	int i;
	for(i =0; i<size;i++){
		if(customers_hash[i]){
			if(customers_hash[i]->cid == cid)
				return customers_hash[i];
		}
	}
	
	return NULL;
}

/**
 *@brief initializes the customer tree
 *
 *@return the root of the new tree
 */
struct C_Product* initCustTree(){

	struct C_Product* newTree = malloc(sizeof(struct C_Product));
	newTree->pid = -1;
	newTree->qty = -1;
	newTree->lc  = NULL;
	newTree->rc  = NULL;
	
	return newTree;
}

/**
 *@brief adds a new product to the customer tree
 *
 *@param tree the tree's root
 *@param product the product to add
 *
 *@return the root of the tree
 */
struct C_Product* addToCustTree(struct C_Product* tree, struct C_Product* product){
	//tree is empty
	
	if(!tree || tree->pid == -1){
		
		tree = product;
		return tree;
	}
	
	if(product->pid == tree->pid){
		tree->qty += product->qty;
		return tree;
	}
	
	
	if(product->pid > tree->pid)
		tree->rc = addToCustTree(tree->rc, product);
	else
		tree->lc = addToCustTree(tree->lc, product);
	printf("\nDONE\n");
	return tree;
}

/**
 *@brief prints all the products for all the customers
 */
void printAllCProducts(){

	struct Customer* cust=NULL;
	int i;
	for(i=0;i<max_customers_g;i++){
		cust = customers_hash[i];
		if(cust){	
			printf("\nCustomer_%d = ",cust->cid);
			printCProducts(cust->shopping_tree);
			printf("\n");
		}
	}
	
}

/**
 *@brief prints the products of a single customer
 *
 *@param root the customer tree's root
 */
void printCProducts(struct C_Product* root){
	if(!root)
		return;
	printCProducts(root->lc);
	printf("<%d,%d>, ",root->pid, root->qty);
	printCProducts(root->rc);
	
}

/**
 *@brief removes a product from a customer's tree
 *
 *@param root the customer's tree root
 *@param pid the product's id
 *
 *@return the tree's root
 */
struct C_Product* removeFromCustomerTree(struct C_Product* root ,int pid){

	if(!root)
		return NULL;
	
	struct C_Product* prod= NULL;
	if(root->pid == pid){
		
		if(!root->lc){
			prod = root->rc;
			free(root);
			return prod;
		}
		else if(!root->rc){
			prod = root->lc;
			free(root);
			return prod;
		}
		
		struct C_Product* prod = minProduct(root->rc);
		root->pid = prod->pid;
		root->qty = prod->qty;
		root->rc = removeFromCustomerTree(root->rc, prod->pid);
		
		return root;
	}
	
	else if(root->pid > pid)
		root->lc = removeFromCustomerTree(root->lc, pid);
	else
		root->rc  = removeFromCustomerTree(root->rc,pid);
	
	return root;
}	

/**
 *@brief finds the product with the lowest pid of a tree
 *
 *@param product the root of the tree
 *
 *@return NULL if the tree is empty, the min product otherwise
 *
 */
struct C_Product* minProduct(struct C_Product* product){
	
	if(!product)
		return NULL;
	
	struct C_Product* temp = product;
	while(temp->lc)
		temp = temp->lc;
	
	return temp;
}

/**
 *@brief transforms a tree to an array
 *
 *@param tree a tree
 *@param table the array to store the tree
 *@param start the position in which to add a product in the table
 *
 */
void treeToTable(struct C_Product* tree, struct C_Product** table, int* start){
	
	if(!tree)
		return;
	struct C_Product* current = tree;
	struct C_Product* temp = NULL;
	
	
	temp = current->lc;
	
	treeToTable(temp, table, start);	
	
	
	table[*start] = makeCProd(current->pid, current->qty);
	
	*start = *start+1;
	temp = current->rc;
	
	treeToTable(temp, table, start);
	
	
	
}

/**
 *@brief prints the contents of a table
 *
 *@param table the table which to print
 *@param size the size of the table
 */
void printTable(struct C_Product** table, int size){

	printf("\nTable: ");
	int i;
	for(i=0; i<size; i++)
		printf("%d, ",table[i]->pid);
	printf("\n");
}

/**
 *@brief buys the products of a customer from the shops
 *
 *@param shop the shop from which to buy
 *@param customer the customer who's buying the products
 *@param table a table with the customer's products
 */
void buyProducts(struct Shop* shop, struct Customer* customer, struct C_Product** table){
	
	if(!shop || shop->sid == -1)
		return;
	//get leftmost shop
	buyProducts(shop->lc, customer, table);
	searchShop(shop, customer, table);
	buyProducts(shop->rc, customer, table);
	
}

/**
 *@brief removes a product from a shop
 *
 *@param shop the shop from whih to remove a product
 *@param prod the product to remove
 *@param prev the the product that comes before prod
 *
 *@return the prev product if prod != prev, the new head of the list otherwise
 */
struct Product* removeShopProduct(struct Shop* shop, struct Product* prod, struct Product* prev){
	if(prod == prev){
		shop->products = prod->next;
		free(prod);
		return shop->products;
	}
	prev->next = prod->next;
	free(prod);	
	return prev;

}

/**
 *@brief searches a shop for the customer's products
 *
 *@param shop shop to search
 *@param customer the customer which buys from the shop
 *@param table a table with the customer's products
 */
void searchShop(struct Shop* shop, struct Customer* customer, struct C_Product** table){
	int ind = 0;
	struct Product* shopProd = shop->products;
	struct Product* prevShopProd = shop->products;
	int customerSize = customer->shopping_size;
	prevShopProd = shopProd;
	while(shopProd && ind<customerSize){
		
		//found prod
		if(table[ind]->pid == shopProd->pid){
			//customer wants more
			if(table[ind]->qty >= shopProd->qty){
				table[ind]->qty -= shopProd->qty;
				shopProd->qty = 0;
				//remove from shop list
				shopProd=removeShopProduct(shop, shopProd, prevShopProd);
				
			}
			
			//shop has more
			else{
				shopProd->qty -= table[ind]->qty;
				table[ind]->qty = 0;
				prevShopProd = shopProd;
				shopProd = shopProd->next;
			}
			
			customerSize = updateCustomerTree(customer, table[ind]);
			
			printCProducts(customer->shopping_tree);
			
		}
		
		else if(table[ind]->pid > shopProd->pid){
			prevShopProd = shopProd;
			shopProd = shopProd->next;
		}
		else
			ind++;
		
	}
}

/**
 *@brief updates a customer's product tree
 *
 *@param customer the customer whose tree to update
 *@param tableProd a customer product in the table
 *
 *@return the new customer shopping tree size
 */
int updateCustomerTree(struct Customer* customer, struct C_Product* tableProd){
	
	struct C_Product* custProd = findInCustTree(customer->shopping_tree, tableProd);
	
	if(!custProd)
		return customer->shopping_size;
	if(!tableProd->qty){
		customer->shopping_tree = removeFromCustomerTree(customer->shopping_tree, custProd->pid);
		customer->shopping_size--;
	}
	else
		custProd->qty = tableProd->qty;
	printf("\ndone\n");
	return customer->shopping_size;
	
}

/**
 *@brief finds a product in a customer's tree
 *
 *@param root the root of the customer's tree
 *@param prod the product to find
 *
 *@return the product if found, NULL otherwise
 */
struct C_Product* findInCustTree(struct C_Product* root, struct C_Product* prod){
	
	if(!root)
		return root;
	if(root->pid == prod->pid)
		return root;
	
	struct C_Product* found = findInCustTree(root->lc, prod);
	if(found)
		return found;
	found = findInCustTree(root->rc, prod);
	return found;
	
}

/**
 *@brief prints a customer's products
 *
 *@param customer the customer whose products to print
 */
void printCustomer(struct Customer* customer){
	printf("Customer_%d = ",customer->cid);
	printCProducts(customer->shopping_tree);
}

/**
 *@brief merges two tables to one
 *
 *@param mergedTable the merged table
 *@param table1 a table to merge
 *@param table2 a table to merge
 *@param size1 table1's size
 *@param size2 table2's ize
 *
 *@return the size of the merged table
 */
int mergeTables(struct C_Product** mergedTable, struct C_Product** table1, struct C_Product** table2, int size1, int size2){
	
	int ind1 = 0,ind2 = 0, mergeInd = 0, totalSize = 0;
	while(ind1 < size1 && ind2<size2){
		if(table1[ind1]->pid < table2[ind2]->pid){
			mergedTable[mergeInd] = makeCProd(table1[ind1]->pid, table1[ind1]->qty);
			ind1++;
		}
		else if(table1[ind1]->pid > table2[ind2]->pid){
			mergedTable[mergeInd] = makeCProd(table2[ind2]->pid, table2[ind2]->qty);
			ind2++;
		}
		else{
			mergedTable[mergeInd] = makeCProd(table1[ind1]->pid, table1[ind1]->qty+table2[ind2]->qty);
			ind1++;
			ind2++;
		}
		totalSize++;
		mergeInd++;
		printTable(mergedTable, totalSize);
		
	}
	
	//table1 leftovers
	while(ind1<size1){
		
		mergedTable[mergeInd] = makeCProd(table1[ind1]->pid, table1[ind1]->qty);	
		ind1++;
		mergeInd++;
		totalSize++;
	}
	
	//table2 leftovers
	while(ind2<size2){
		
		
		mergedTable[mergeInd] = makeCProd(table2[ind2]->pid, table2[ind2]->qty);	
		ind2++;
		mergeInd++;
		totalSize++;
	}
	
	printf("\ndone\n");
	return totalSize;
}

/**
 *@brief transform a table to a binary tree
 *
 *@param table the table to turn into a tree
 *@param start the start of the rable
 *@param end the end of the table
 *
 *@return the root of the tree created
 */
struct C_Product* tableToTree(struct C_Product** table, int start, int end){
	if(start == end)
		return NULL;
	
	int mid = (start+end)/2;
	struct C_Product* root = makeCProd(table[mid]->pid, table[mid]->qty);
	root->lc = tableToTree(table, start, mid);
	root->rc = tableToTree(table, mid+1, end);
	return root;
}

/**
 *@brief gets the first digit of an integer
 *
 *@param N an integer
 *
 *@return N's first digit
 */
int getFirstDigit(int N){
	while(N>10)
		N/=10;
	return N;
}
/**
 * @brief Optional function to initialize data structures that 
 *        need initialization
 *
 * @return 1 on success
 *         0 on failure
 */
int Initialize (void)
{
	
	//init shop tree
	shopSentinel = malloc(sizeof(struct Shop));
	shopSentinel->sid = -1;
	shopSentinel->type = -1;
	shopSentinel->products = NULL;
	shopSentinel->lc = NULL;
	shopSentinel->rc = NULL;
	
	shopRoot = shopSentinel;
	
	customers_hash = NULL;
	int i = 0;
	//init shopTypes
	for(i=0;i<5;i++)
		ShopTypes[i] = NULL;
	
	
	
	return 1;
}

/**
 * @brief Register shop 
 *
 * @param sid   The shop's id
 * @param type  The shop's type
 *
 * @return 1 on success
 *         0 on failure
 */
int RegisterShop (int sid, int type)
{
	if(shopRoot == shopSentinel){
		struct Shop* newShop = makeNewShop(sid, type);
		shopRoot = newShop;
		PrintShops();
		return 1;
	}
	
	struct Shop* shopIter = shopRoot;
	struct Shop* shopParent = shopRoot;
	
	while(shopIter!=shopSentinel){
		shopParent = shopIter;	
		
		if(shopIter->sid == sid){
			printf("\nStore already in\n");
			return 0;
		}
		if(shopIter->sid > sid)	
			shopIter = shopIter->lc;
		else
			shopIter = shopIter->rc;
			
	}
	struct Shop* newShop = makeNewShop(sid, type);
	if(shopParent->sid > sid)
		shopParent->lc = newShop;
	else
		shopParent->rc = newShop;
	
	//PrintShops();
	return 1;
}

/**
 * @brief Supply shop 
 *
 * @param sid       The shop's id
 * @param pid       The product's id
 * @param quantity  The product's quantity
 * @param price     The product's price
 *
 * @return 1 on success
 *         0 on failure
 */
int SupplyShop (int sid, int pid, int quantity, int price)
{
	
	struct Shop* shop = findShop(sid);
	if(!shop)
		return 0;
	
	struct Product* prod = shop->products;
	struct Product* iter = shop->products;
	while(iter){
		if(iter->pid == pid){
			prod->qty+=quantity;
			//PrintProducts();
			return 1;
		}
		else if(iter->pid < pid){
			prod = iter;
			iter = iter->next;
		}
		else
			break;
	}
	
	struct Product* newProd = makeNewProd(pid, quantity, price);
	if(!prod)
		shop->products = newProd;
	else{
		newProd->next = iter;
		if(prod!=iter)
			prod->next = newProd;
		else
			shop->products = newProd;
	}
	//PrintProducts();
	return 1;
}

/**
 * @brief Register customer
 *
 * @param cid The customer's id
 *
 * @return 1 on success
 *         0 on failure
 */
int RegisterCustomer (int cid)
{
	customers_hash = initHash();
	
	int size  = selectTableSize();
	int index = customerIndex(cid, size);
	struct Customer* newCustomer = makeCustomer(cid);
	customers_hash[index] = newCustomer;
	PrintCustomers();
	
	
	return 1;
}

/**
 * @brief Add to shopping list
 *
 * @param cid       The customer's id
 * @param pid       The product's id
 * @param quantity  The quantity of the product
 *
 * @return 1 on success
 *         0 on failure
 */
int AddToShoppingList (int cid, int pid, int quantity)
{
	
	struct Customer* customer = NULL;
	customer = findCustomerInTable(cid);
	//customer not found
	if(!customer)
		return 0;	

	
	struct C_Product* product = makeCProd(pid, quantity); 
	//empty tree
	if(!customer->shopping_size)
		customer->shopping_tree = initCustTree();
	
	customer->shopping_tree = addToCustTree(customer->shopping_tree, product);
	customer->shopping_size++;
	
	printAllCProducts();
	return 1;
}

/**
 * @brief Delete from shopping list
 *
 * @param cid  The customer's id
 * @param pid  The product's id
 * 
 * @return 1 on success
 *         0 on failure
 */
int DeleteFromShoppingList (int cid, int pid)
{
	
	struct Customer* customer = findCustomerInTable(cid);
	//customer not found
	if(!customer)
		return 0;
	//empty tree
	if(!customer->shopping_size)
		return 0;
	
	struct C_Product* tree = removeFromCustomerTree(customer->shopping_tree, pid);
	//item not found
	if(!tree)
		return 0;
	
	customer->shopping_tree = tree;
	customer->shopping_size--;
	
	printAllCProducts();
	return 1;
}

/**
 * @brief Go shopping
 *
 * @param cid The customer's id
 *
 * @return 1 on success
 *         0 on failure
 */
int GoShopping (int cid)
{
	struct Customer* customer = findCustomerInTable(cid);
	
	//customer not found
	if(!customer)
		return 0;
	int start = 0;
	struct C_Product** products = malloc(customer->shopping_size*sizeof(struct C_Product*));
	treeToTable(customer->shopping_tree, products, &start);
	printTable(products, customer->shopping_size);
	
	buyProducts(shopRoot, customer, products);
	printCustomer(customer);
	PrintProducts();
	
	
	return 1;
}

/**
 * @brief Customers shop together
 * 
 * @param cid1  The id of the first customer
 * @param cid2  The id of the second customer
 *
 * @return 1 on success
 *         0 on failure
 */
int ShopTogether (int cid1, int cid2)
{
	printf("\nMerge\n");
	struct Customer* cust1 = findCustomerInTable(cid1);
	struct Customer* cust2 = findCustomerInTable(cid2);
	//customer not found
	if(!cust1 || !cust2)
		return 0;
	printf("\noka\n");
	int i=0,j=0, totalSize = 0;
	struct C_Product** table1 = malloc(cust1->shopping_size*sizeof(struct C_Product*)); 
	struct C_Product** table2 = malloc(cust2->shopping_size*sizeof(struct C_Product*));  
	struct C_Product** mergedTable = malloc((cust1->shopping_size+cust2->shopping_size)*sizeof(struct C_Product*));
	treeToTable(cust1->shopping_tree, table1, &i);
	treeToTable(cust2->shopping_tree, table2, &j);
	totalSize = mergeTables(mergedTable, table1, table2, cust1->shopping_size, cust2->shopping_size);
	printTable(mergedTable,totalSize);
	cust1->shopping_tree = tableToTree(mergedTable, 0, totalSize-1);
	printCProducts(cust1->shopping_tree);
	printf("\ndone\n");
	
	//removeCustomerFromTable(cust2);
	return 1;
}

/**
 * @brief Categorize shops
 *
 * @return 1 on success
 *         0 on failure
 */
int CategorizeShops (void)
{
	
	int current_val = 5;
	int prev_val = 5;
	int firstDigit = -1;
	struct Shop* shop = shopRoot;
	struct Shop* add = NULL;
	struct Shop* addRoot= NULL;
	while(current_val>1){
		firstDigit = getFirstDigit(shop->sid);
		if(current_val == firstDigit)
			addRoot = shop;
		else
			addRoot = NULL;
		
		while(current_val == getFirstDigit(shop->sid)){
			add = shop;
			add->rc = shop->rc;
			add->lc = NULL;
			add = add->lc;
			shop = shop->lc;
			if(!shop)
				break;
		}
		ShopTypes[current_val-1] = addRoot;
		current_val--;
	}
	add = shop;
	ShopTypes[current_val-1]=add;
	printCategories();
	return 1;
}

/**
 * @brief Print shops
 *
 * @return 1 on success
 *         0 on failure
 */
int PrintShops (void)
{
	fflush(stdout);
	printf("\nShops: ");
	ShopPrint(shopRoot,0);
	printf("\n");
	return 1;		
	
}




/**
 * @brief Print customers
 *
 * @return 1 on success
 *         0 on failure
 */
int PrintCustomers (void)
{
	int size = selectTableSize();
	printf("\nCustomers: ");
	int i;
	for(i=0; i<size; i++){
		if((customers_hash[i]))
			printf("%d, ",customers_hash[i]->cid);
		
	}
	printf("\n");
	return 1;
}

/**
 * @brief Free resources
 *
 * @return 1 on success
 *         0 on failure
 */
int FreeAll(void)
{
	
	return 1;
}


/**
 * @brief The main function
 *
 * @param argc Number of arguments
 * @param argv Argument vector
 *
 * @return 0 on success
 *         1 on failure
 */
int main(int argc, char** argv)
{
	FILE *fin = NULL;
	char buff[BUFFER_SIZE], event;

	/* Check command buff arguments */
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <input_file> \n", argv[0]);
		return EXIT_FAILURE;
	}

	/* Open input file */
	if (( fin = fopen(argv[1], "r") ) == NULL ) {
		fprintf(stderr, "\n Could not open file: %s\n", argv[1]);
		perror("Opening test file\n");
		return EXIT_FAILURE;
	}

	/* Initializations */
	Initialize();

	/* Read input file buff-by-buff and handle the events */
	while (fgets(buff, BUFFER_SIZE, fin)) {

		DPRINT("\n>>> Event: %s", buff);

		switch(buff[0]) {

			/* Comment */
			case '#':
				break;

			/* dummy event '0'. Get the total number of customers */
			case '0':
				{
					sscanf(buff, "%c %u", &event, &max_customers_g);
					DPRINT("%c MAX CUSTOMERS: %u\n", event, max_customers_g);
					break;
				}

				/* Register shop
				 * R <sid> <type> */
			case 'R':
				{
					int sid, type;

					sscanf(buff, "%c %d %d", &event, &sid, &type);
					DPRINT("%c %d %d\n", event, sid, type);

					if (RegisterShop(sid, type)) {
						DPRINT("%c %d %d succeeded\n", event, sid, type);
					} else {
						fprintf(stderr, "%c %d %d failed\n", event, sid, type);
					}

					break;
				}

				/* Supply shop
				 * S <sid> <pid> <quantity> <price> */
			case 'S':
				{
					int sid, pid, quantity, price;

					sscanf(buff, "%c %d %d %d %d", &event, &sid, &pid, &quantity, &price);
					DPRINT("%c %d %d %d %d\n", event, sid, pid, quantity, price);

					if (SupplyShop(sid, pid, quantity, price)) {
						DPRINT("%c %d %d %d %d succeeded\n", event, sid, pid, quantity, price);
					} else {
						fprintf(stderr, "%c %d %d %d %d failed\n", event, sid, pid, quantity, price);
					}

					break;
				}

				/* Register customer
				 * C <cid> */
			case 'C':
				{
					int cid;

					sscanf(buff, "%c %d", &event, &cid);
					DPRINT("%c %d\n", event, cid);

					if (RegisterCustomer(cid)) {
						DPRINT("%c %d succeeded\n", event, cid);
					} else {
						fprintf(stderr, "%c %d failed\n", event, cid);
					}

					break;
				}

				/* Add to shopping list
				 * L <cid> <pid> <quantity> */
			case 'L':
				{
					int cid, pid, quantity;

					sscanf(buff, "%c %d %d %d", &event, &cid, &pid, &quantity);
					DPRINT("%c %d %d %d\n", event, cid, pid, quantity);

					if (AddToShoppingList(cid, pid, quantity)) {
						DPRINT("%c %d %d %d succeeded\n", event, cid, pid, quantity);
					} else {
						fprintf(stderr, "%c %d %d %d failed\n", event, cid, pid, quantity);
					}

					break;
				}

				/* Delete from shopping list
				 * D <cid> <pid> */
			case 'D':
				{
					int cid, pid;

					sscanf(buff, "%c %d %d", &event, &cid, &pid);
					DPRINT("%c %d %d\n", event, cid, pid);

					if (DeleteFromShoppingList(cid, pid)) {
						DPRINT("%c %d %d succeeded\n", event, cid, pid);
					} else {
						fprintf(stderr, "%c %d %d failed\n", event, cid, pid);
					}

					break;
				}

				/* Go shopping
				 * G <cid> */
			case 'G':
				{
					int cid;

					sscanf(buff, "%c %d", &event, &cid);
					DPRINT("%c %d\n", event, cid);

					if (GoShopping(cid)) {
						DPRINT("%c %d succeeded\n", event, cid);
					} else {
						fprintf(stderr, "%c %d failed\n", event, cid);
					}

					break;
				}

				/* Shop together
				 * M <cid1> <cid2> */
			case 'M':
				{
					int cid1, cid2;

					sscanf(buff, "%c %d %d", &event, &cid1, &cid2);
					DPRINT("%c %d %d\n", event, cid1, cid2);

					if (ShopTogether(cid1, cid2)) {
						DPRINT("%c %d %d succeeded\n", event, cid1, cid2);
					} else {
						fprintf(stderr, "%c %d %d failed\n", event, cid1, cid2);
					}

					break;
				}

				/* Categorize shops
				 * T */
			case 'T':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (CategorizeShops()) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}

				/* Print shops
				 * X */
			case 'X':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (PrintShops()) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}

				/* Print customers
				 * Y */
			case 'Y':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (PrintCustomers()) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}

				/* Empty line */
			case '\n':
				break;

				/* Ignore everything else */
			default:
				DPRINT("Ignoring buff: %s \n", buff);

				break;
		}
	}

	FreeAll();
	return (EXIT_SUCCESS);
}
