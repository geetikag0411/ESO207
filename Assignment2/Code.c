#include <stdio.h>
#include <stdlib.h>
// struct node is the basic data structure of a node
// space complexity of our code is o(m)
// timecomplexity for creating row links is o(m)
//  worst case timecomplexity for creating column links is o(m^2)
struct node
{
    int data;
    int row;
    int col;
    struct node *below;
    struct node *next;
};
// currrow keeps track of the row that is currently being added
// currelementinnext keeps track of the position next to which a new element will be added in a row

struct node *currrow;
struct node *currelementinnext;
// horizontaltraversal adds a new element in the current row and updates currelementinnext;
// time complexity is O(1)
void horizontaltraversal(struct node *o, struct node *element)
{
    currelementinnext->next = element;
    currelementinnext = element;
}
// createrowindexed creates the row links
// timecomplexity o(1)
void createrowindexed(struct node **head, struct node *element)
{
    if (*head == NULL)
    {
        struct node *o = (struct node *)malloc(sizeof(struct node));
        o->row = element->row;
        o->col = -1;
        o->data = -1;
        o->below = NULL;
        o->next = NULL;
        *head = o;
        currrow = o;
        currelementinnext = o;
        horizontaltraversal(o, element);
        return;
    }
    if (element->row == currrow->row)
    {
        horizontaltraversal(currrow, element);
    }
    else
    {
        struct node *o = (struct node *)malloc(sizeof(struct node));
        o->row = element->row;
        o->col = -1;
        o->data = -1;
        o->below = NULL;
        o->next = NULL;
        currrow->below = o;
        currrow = o;
        currelementinnext = o;
        horizontaltraversal(o, element);
    }
}
// add a element vertically in a column
// time complexity o(d) where d is the number of node currently in a particular column
void verticaltraversal(struct node *o, struct node *element)
{
    struct node *u = o;
    while (u->below != NULL)
    {
        u = u->below;
    }
    u->below = element;
}
// createcolindexed creates column links
// worst case timecomplexity o(m)
void createcolindexed(struct node **head, struct node *element)
{
    if (*head == NULL)
    {
        struct node *o = (struct node *)malloc(sizeof(struct node));
        o->row = -1;
        o->col = element->col;
        o->data = -1;
        o->below = NULL;
        o->next = NULL;
        *head = o;
        verticaltraversal(o, element);
        return;
    }
    struct node *temp = *head;
    struct node *prev = *head;
    while (temp != NULL && element->col >= temp->col)
    {
        if (temp->col == element->col)
        {
            verticaltraversal(temp, element);
            break;
        }
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
    {
        struct node *o = (struct node *)malloc(sizeof(struct node));
        o->row = -1;
        o->col = element->col;
        o->data = -1;
        o->below = NULL;
        o->next = NULL;
        prev->next = o;
        verticaltraversal(o, element);
    }
    else if (element->col < temp->col)
    {
        struct node *o = (struct node *)malloc(sizeof(struct node));
        o->row = -1;
        o->col = element->col;
        o->data = -1;
        o->below = NULL;
        o->next = NULL;
        o->next = temp;
        if (temp == *head)
            *head = o;
        else
            prev->next = o;
        verticaltraversal(o, element);
    }
}
// calprd calculates product for a particular row and column;
int calprd(struct node *itrow, struct node *itcol)
{
    // in itrow traverse next and in itcol  traverse below
    struct node *r = itrow->next;
    struct node *c = itcol->below;
    int sum = 0;
    while (r != NULL && c != NULL)
    {
        if (r->col == c->row)
        {
            sum += (r->data) * (c->data);
            r = r->next;
            c = c->below;
        }
        else if (r->col > c->row)
        {
            c = c->below;
        }
        else if (r->col < c->row)
        {
            r = r->next;
        }
    }
    return sum;
}
int main()
{
    int n;
    scanf("%d", &n);
    struct node *headrow1 = NULL;
    struct node *headrow2 = NULL;
    struct node *headcol1 = NULL;
    struct node *headcol2 = NULL;
    while (1)
    {
        int mat;
        scanf("%d", &mat);
        if (mat == 0)
            break;
        int row, col, data;
        scanf("%d %d %d", &row, &col, &data);

        struct node *t = (struct node *)malloc(sizeof(struct node));
        t->row = row;
        t->col = col;
        t->data = data;
        t->next = NULL;
        t->below = NULL;
        if (mat == 1)
        {
            createrowindexed(&headrow1, t);
            createcolindexed(&headcol1, t);
        }
        if (mat == 2)
        {
            createrowindexed(&headrow2, t);
            createcolindexed(&headcol2, t);
        }
    }
    // multiply the matrix using row indexed of mat1 and colindexed of mat2;
    struct node *itrow = headrow1;
    int flag = 0;
    while (itrow != NULL)
    {
        struct node *itcol = headcol2;

        while (itcol != NULL)
        {
            // traverse in itrow and itcolumn
            int sum = calprd(itrow, itcol);
            if (sum != 0)
            {
                flag = 1;
                printf("%d %d %d\n", itrow->row, itcol->col, sum);
            }
            itcol = itcol->next;
        }
        itrow = itrow->below;
    }
    if (flag == 0)
        printf("NULL MATRIX!");

    return 0;
}
