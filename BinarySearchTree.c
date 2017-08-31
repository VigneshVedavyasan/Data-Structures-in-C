
#include<stdio.h>
#include<stdlib.h>

struct ListNode
{
    int info;
    struct ListNode *lChild;
    struct ListNode *rChild;
};

struct ListNode* insertElement(struct ListNode* node,int data)
{
    if(node==NULL)
    {
    struct ListNode* temp=(struct ListNode*)malloc(sizeof(struct ListNode));
    temp->info=data;
    temp->lChild=NULL;
    temp->rChild=NULL;
    return temp;
    }
    else if(node->info>=data)
        node->lChild=insertElement(node->lChild,data);
    else
        node->rChild=insertElement(node->rChild,data);
    return node;
}
struct ListNode* findMin(struct ListNode* node)
{
    if(node==NULL)
        return NULL;
    if(node->lChild!=NULL)
        return findMin(node->lChild);
    else
        return node;
}
struct ListNode* deleteElement(struct ListNode* node,int data)
{
    struct ListNode* temp;
    if(node==NULL)
        printf("Element not found!");
    else if(node->info>data)
        node->lChild=deleteElement(node->lChild,data);
    else if(node->info<data)
        node->rChild=deleteElement(node->rChild,data);
    else
    {
        if(node->lChild!=NULL && node->rChild!=NULL)
        {
            temp=findMin(node->rChild);
            node->info=temp->info;
            node->rChild=deleteElement(node->rChild,temp->info);
        }
        else
        {
            temp=node;
            if(node->lChild==NULL)
                node=node->rChild;
            else if(node->rChild==NULL)
                node=node->rChild;
            else
            {
                temp=node;
                if(node->lChild==NULL)
                    node=node->rChild;
                else if(node->rChild==NULL)
                    node=node->lChild;
                free(temp);
            }

        }

    }
    return node;
}

int search(struct ListNode* node,int data)
{
    if(node==NULL)
        return 0;
    else if(node->info<data)
        return search(node->rChild,data);
    else if(node->info>data)
        return search(node->lChild,data);
    else
        return 1;
}

void printInorder(struct ListNode *node)
{
        if(node==NULL)
        {
            return;
        }
        printInorder(node->lChild);
        printf("%d ",node->info);
        printInorder(node->rChild);
}

void main()
{
    struct ListNode* root=NULL;
    int data,choice,c;

    while(1)
    {
        printf("\n1. Insert element\n2. Delete element\n3. Search element\n4. Inorder Traversal\n5. Preorder Traversal\n6. Postorder Traversal\n7. Exit. > ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            printf("\nEnter the value of tree node > ");
            scanf("%d",&data);
            root=insertElement(root,data);
            break;
        case 2:
            scanf("%d",&data);
            if(root==NULL)
                printf("\nNo node to delete");
            root=deleteElement(root,data);
            break;
        case 3:
            scanf("%d",&c);
            if(search(root,c))
                printf("\nThe element is present in the BST");
            break;
        case 4:
            printf("\n");
            printInorder(root);
            break;
        case 7:
            exit(0);
            break;

        }
    }
}
