#include <stdio.h>
#include <jansson.h>

int main(void){
    char text[] = "{\"out\":[[0.2,15],[0.5,3.3],[0.1,46.8]],\"in\":[[0.6,20.2],[0.04,66.654],[0.0124,1.5]]}";
    json_error_t error;
    json_t *root;
    json_t *in, *out, *obj;
    json_t *array, *element;
    double value;
    const char *key;
    int i, j;
    root = json_loads(text, 0, &error);
    if(!root){
        fprintf(stderr, "error : root\n");
        fprintf(stderr, "error : on line %d: %s\n", error.line, error.text);
        exit(1);
    }
    in = json_object_get(root, "in");
    if(!json_is_array(in)){
        printf("NG1\n");
    }
    array = json_array_get(in, 1);
    if(!json_is_array(array)){
        fprintf(stderr,"NG2\n");
    }
    element = json_array_get(array, 1);
    value = json_real_value(element);
    printf("%f\n", value);//66.654000

    out = json_object_get(root, "out");
    array = json_array_get(out, 2);
    json_array_foreach(array, i, element){
        value = json_real_value(element);
        printf("%f ", value);//0.100000 46.800000
    }
    printf("\n");

    json_object_foreach(root, key, obj){
        printf("%s:\n", key);
        json_array_foreach(obj, i, array){
            json_array_foreach(array, j, element){
                value = json_number_value(element);//json_real_value NG for 15 
                printf("%f ", value);
            }
            printf("\n");
        }
        printf("\n");
    }
/*
out:
0.200000 15.000000
0.500000 3.300000
0.100000 46.800000

in:
0.600000 20.200000
0.040000 66.654000
0.012400 1.500000
*/
    return 0;
}
