#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *transformToRFormat(char *instruction);

char *transformToIFormat(char *instruction);

char *assign_register(char *register_value);

char *to_binary_string(char *address);

char *to_4_binary_string(char *address);


int main() {


    //variable
    FILE *fp;
    char *buffer;
    long file_size;

    char delimiter[] = "\n";
    char *instruction;

    // open the file
    fp = fopen("../test.s", "rb");

    //load file failed
    if (fp == NULL) {
        printf("failed to open file\n");
        return 1;
    }
    //load file successes
    fseek(fp, 0, SEEK_END);
    file_size = ftell(fp);
    rewind(fp);

    buffer = (char *) malloc(sizeof(char) * file_size);
    if (buffer == NULL) {
        printf("Failed to allocate memory\n");
        return 1;
    }

    fread(buffer, sizeof(char), file_size, fp);

    //close file
    fclose(fp);

    //TO DO
    instruction = strtok(buffer, delimiter);
    for (int i = 0; i < 10; ++i) {

        char op_type[10];
        sscanf(instruction, "%[a-z]", op_type);
        //printf("op_type:%s\n", op_type);

        if (strcmp(op_type, "add") == 0 || strcmp(op_type, "sub") == 0) {
            //printf("instruction:%s\n",instruction);
            transformToRFormat(instruction);

        } else if (strcmp(op_type, "addi") == 0 || strcmp(op_type, "lw") == 0 || strcmp(op_type, "sw") == 0) {
            //printf("instruction:%s\n",instruction);
            transformToIFormat(instruction);
        }
        instruction = strtok(NULL, delimiter);
    }

    //free memory
    free(buffer);
    return 0;
}

char *transformToRFormat(char *instruction) {

    char op[7], rs[6], rt[6], rd[6], shamt[6], funct[7];
    char op_copy[7];

    //op
    strcpy(op, "000000");
    //printf("op:%s\n",op);

    //rd
    sscanf(instruction, "%*s%*$%s", rd);
    sscanf(rd, "%[^,]", rd);
    strcpy(rd, assign_register(rd));
    //printf("rd:%s\n",rd);

    //rs
    sscanf(instruction, "%*s%*s%*$%s", rs);
    sscanf(rs, "%[^,]", rs);
    strcpy(rs, assign_register(rs));
    //printf("rs:%s\n",rs);

    //rt
    sscanf(instruction, "%*s%*s%*s%*$%s", rt);
    strcpy(rt, assign_register(rt));
    //printf("rt:%s\n",rt);

    //shamt
    strcpy(shamt, "00000");
    //printf("shamt:%s\n",shamt);

    //funct
    sscanf(instruction, "%[a-z]", op_copy);
    if (strcmp(op_copy, "add") == 0) {
        strcpy(funct, "100000");
    } else if (strcmp(op_copy, "sub") == 0) {
        strcpy(funct, "010000");
    }
    //printf("funct:%s\n",funct);

    printf("%s%s%s%s%s%s\n", op, rs, rt, rd, shamt, funct);
};

char *transformToIFormat(char *instruction) {
    char op[7], rs[6], rt[6], address[17];


    sscanf(instruction, "%s", op);
    if (strcmp(op, "addi") == 0) {

        //op
        strcpy(op, "100000");
        //printf("op:%s\n",op);

        //rt
        sscanf(instruction, "%*s%*$%s", rt);
        strcpy(rt, assign_register(rt));
        //printf("rt:%s\n",rt);

        //rs
        sscanf(instruction, "%*s%*s%*$%s", rs);
        sscanf(rs, "%[^,]", rs);
        strcpy(rs, assign_register(rs));
        //printf("rs:%s\n",rs);

        printf("%s%s%s", op, rs, rt);

        //address
        sscanf(instruction, "%*s%*s%*s%s", address);
        strcpy(address, to_binary_string(address));
        //printf("address:%s\n",address);

    }
    if (strcmp(op, "lw") == 0) {

        //rt
        sscanf(instruction, "%*s%*$%s", rt);
        strcpy(rt, assign_register(rt));
        //printf("rt:%s\n",rt);

        //address
        sscanf(instruction, "%*s%*s%2s", address);
        strcpy(address, to_4_binary_string(address));
        //printf("address:%s\n",address);

        //rs
        sscanf(instruction, "%*s%*s%s", rs);
        sscanf(rs, "%*[^$]%*$%[^)]", rs);
        strcpy(rs, assign_register(rs));
        //printf("rs:%s\n",rs);

        //op
        strcpy(op, "000001");
        //printf("op:%s\n",op);

        printf("%s%s%s%s\n", op, rs, rt, address);
    }
    if (strcmp(op, "sw") == 0) {

        //rt
        sscanf(instruction, "%*s%*$%s", rt);
        strcpy(rt, assign_register(rt));
        //printf("rt:%s\n",rt);

        //address
        sscanf(instruction, "%*s%*s%2s", address);
        strcpy(address, to_4_binary_string(address));
        //printf("address:%s\n",address);

        //rs
        sscanf(instruction, "%*s%*s%s", rs);
        sscanf(rs, "%*[^$]%*$%[^)]", rs);
        strcpy(rs, assign_register(rs));
        //printf("rs:%s\n",rs);

        //op
        strcpy(op, "000010");
        //printf("op:%s\n",op);

        printf("%s%s%s%s", op, rs, rt, address);
    }

    return instruction;
}


enum {
    t0, t1, t2, t3, t4, t5, t6, t7, t8, t9
};
enum {
    s0, s1, s2, s3, s4, s5, s6, s7
};

//register_value=t0, register_type=t, register_number=0
char *assign_register(char *register_value) {

    char register_type[1];
    sscanf(register_value, "%[a-z]", register_type);

    if ((strstr(register_type, "t")) != NULL) {

        char register_number[1];
        sscanf(register_value, "%*[a-z]%s", register_number);
        int number = atoi(register_number);

        switch (number) {
            case t0:
                return "01000";
            case t1:
                return "01001";
            case t2:
                return "01010";
            case t3:
                return "01011";
            case t4:
                return "01100";
            case t5:
                return "01101";
            case t6:
                return "01110";
            case t7:
                return "01110";
            case t8:
                return "01000";
            case t9:
                return "01000";
            default:
                return NULL;
        }
    } else if ((strstr(register_type, "s")) != NULL) {

        char register_number[1];
        sscanf(register_value, "%*[a-z]%s", register_number);
        int number = atoi(register_number);

        switch (number) {
            case s0:
                return "10000";
            case s1:
                return "10001";
            case s2:
                return "10010";
            case s3:
                return "10011";
            case s4:
                return "10100";
            case s5:
                return "10101";
            case s6:
                return "10110";
            case s7:
                return "10111";
            default:
                return NULL;
        }
    } else {
        return NULL;
    }
}

char *to_binary_string(char *address) {
    int num;
    num=atoi(address);
    short bits = (short) num;
    for (int i = 15; i >= 0; i--) {
        printf("%d", (bits >> i) & 1);
    }
    printf("\n");
    return address;
}

char *to_4_binary_string(char *address) {
    int num;
    num = atoi(address);
    char *binaryNum = (char *) malloc(17 * sizeof(char));
    memset(binaryNum, '0', 16);
    binaryNum[16] = '\0';
    int i = 15;
    while (num > 0) {
        binaryNum[i] = num % 2 + '0';
        num = num / 2;
        i--;
    }
    return binaryNum;
}