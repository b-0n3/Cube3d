#include "util.h"

t_array_list *ft_split_property(char *line)
{
    t_array_list *words;
    int          i;
 
        words =(t_array_list *) malloc(sizeof(t_array_list));
        new_array_list(words,2,sizeof(char *));
    if (line != NULL )
    {
            i =0;
            while (!ft_iswhitespace(line[i]))
                i++;
            words->push(words , ft_substr(line , 0 , i),sizeof(char *));
            if ( ft_strlen(line) > i)
                words->push(words, ft_substr(line, i ,ft_strlen(line) - i), sizeof(char*));
            return words;
    }
    return words;
}



// void  print(void  *l)
// {
//     char *line = (char *) l;
//     printf("{%s}\n",line);
   
// }

// // @test
// int main()
// {
//     char *test1 = "CS sadfsdaf";
//     char *test2 = "CSasdf";
//     char *test3 = "CS    ";
//     char *test4 = "CS  sdf";
//     char *test5 = "";
//     char *test6 = "Cs sadf";
//     char *test7 = "n la lsd lsdfl ";
//     char *test8 = "CS sdaf  sdf asdf  sdff sddff sadasddf sdf";
//     char *test9 = "CS as asd df asddfas asddfa asddf ";
//     t_array_list *wo;
//     printf("___________________");
//     wo = ft_split_property(test1);
//      printf("%s\n %s \n", "testing\n", test1);
//     wo->foreach(wo , &print);
//      printf("%zu",wo->index);
//      wo->free(wo , &free);
//      free(wo);
//       printf("___________________");
//     wo = ft_split_property(test2);
//      printf("%s\n %s \n", "testing\n", test2);
//     wo->foreach(wo , &print);
//      printf("%zu",wo->index);
//      wo->free(wo , &free);
//      free(wo);
//       printf("___________________");
//     wo = ft_split_property(test3);
//      printf("%s\n %s \n", "testing\n", test3);
//     wo->foreach(wo , &print);
//      printf("%zu",wo->index);
//      wo->free(wo , &free);
//      free(wo);
//       printf("___________________");
//     wo = ft_split_property(test4);
//      printf("%s\n %s \n", "testing\n", test4);
//     wo->foreach(wo , &print);
//      printf("%zu",wo->index);
//      wo->free(wo , &free);
//      free(wo);
//       printf("___________________");
//     wo = ft_split_property(test5);
//      printf("%s\n %s \n", "testing\n", test5);
//     wo->foreach(wo , &print);
//      printf("%zu",wo->index);
//      wo->free(wo , &free);
//      free(wo);
//       printf("___________________");
//     wo = ft_split_property(test6);
//      printf("%s\n %s \n", "testing\n", test6);
//     wo->foreach(wo , &print);
//      printf("%zu",wo->index);
//      wo->free(wo , &free);
//      free(wo);
//       printf("___________________");
//     wo = ft_split_property(test7);
//      printf("%s\n %s \n", "testing\n", test7);
//     wo->foreach(wo , &print);
//      printf("%zu",wo->index);
//      wo->free(wo , &free);
//      free(wo);
//       printf("___________________");
//     wo = ft_split_property(test8);
//      printf("%s\n %s \n", "testing\n", test8);
//     wo->foreach(wo , &print);
//      printf("%zu",wo->index);
//      wo->free(wo , &free);
//      free(wo);
//       printf("___________________");
//     wo = ft_split_property(test9);
//      printf("%s\n %s \n", "testing\n", test9);
//     wo->foreach(wo , &print);
//      printf("%zu",wo->index);
//      wo->free(wo , &free);
//      free(wo);
     
//        printf("___________________ NULL ");
//     wo = ft_split_property(NULL);
//     // printf("%s\n %s \n", "testing\n", test9);
//     wo->foreach(wo , &print);
//      printf("%zu",wo->index);
//      wo->free(wo , &free);
//      free(wo);

// } 

