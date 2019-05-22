typedef struct Node
{
    int value;
    int count;
    struct Node *next;

}Node;

typedef struct RecentNodes
{
    Node *head;
    Node *tail;
    int maxNodes;
    int nodes;
}RecentNodes;

void initialize(RecentNodes *, int);
void isKeyRecent(RecentNodes *, int);
void delete_ll(RecentNodes *List, int ele);
void printRecent(RecentNodes );
