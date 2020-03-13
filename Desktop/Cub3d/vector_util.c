#include "Cube3d.h"

t_vector newVector(t_vector *this,float x, float y)
{
    this->x = x;
    this->y = y;
    
    this->length = &length;
    this->add = &add;
    this->sub = &sub;
    this->len = this->length(this);
    this->compare_to  = &compare_to;
    return *this;
}

float length(t_vector *this)
{
    return ((float) sqrt((this->x * this-> x) + (this->y * this->y)));
}

void add(t_vector *this , t_vector *o)
{
     this->x += o->x;
    this->y += o->y;
    this->len = this->length(this);
}

void sub(t_vector *this, t_vector *o)
{
     this->x -= o->x;
    this->y -= o->y;
    this->len = this->length(this);
}

t_bool con(void *item)
{
    t_vector *vert1 = (t_vector *) item;
    if (vert1-> len  <= 4.0f)
        return TRUE;
    return FALSE;
}
int compare_to(void  *this , void *o)
{
    if (((t_vector *) this)->len < ((t_vector *)o)->len)
        return  1;
    if (((t_vector *) this)->len > ((t_vector *)o)->len)
        return  -1;
    return 0;
}
void printVer(void *item)
{
    if(item != NULL)
    {
     t_vector *vert1 = (t_vector *) item;
    
   printf(" v1(x=%f , y=%f)len = |%f| \n", 
    vert1->x,vert1->y , vert1->len );
    }
    }
int main(void)
{
    t_vector vert1;
    t_vector vert2;

     newVector(&vert1, 1212.0f, 152.0f);
     newVector(&vert2, 123.0f, 152.0f);
    t_vector vert3;

     newVector(&vert3, -3.0f, -2.0f);
    t_array_list arraylist;
       
        new_array_list(&arraylist, 1, sizeof(t_vector  ),3 );
        arraylist.push(&arraylist,(void *) &vert1, sizeof(vert1 ));
        arraylist.push(&arraylist,(void*) &vert2, sizeof(vert2 ));
        arraylist.push(&arraylist, (void *) &vert3, sizeof(vert3 ));
        arraylist.foreach(&arraylist, &printVer);
        arraylist.sort(&arraylist, vert1.compare_to , 0 ,(int )(arraylist.index - 1));
        printf("after sort \n");
        arraylist.foreach(&arraylist, &printVer);
        arraylist.delete_if(&arraylist, con ,NULL);
        //newVector(&vert3, -51.0f,-45487.0f);
       // arraylist.update_at(&arraylist, (void*) &vert2, 2);
        arraylist.foreach(&arraylist, &printVer);
        //arraylist._free(&arraylist, NULL);
        //printVer(arraylist.get(&arraylist, ));
        //system("leaks a.out");
}

