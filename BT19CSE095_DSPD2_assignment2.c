//Anjali Rengade BT19CSE095
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#define m 5
#define DATA_SIZE 3
#define MIN_DATASIZE 2
#define MAX 4
#define MIN 2

int NumRecords=0;
typedef struct accommodation
{
    char firstname [50];
    char lastname [50];
    char accommodation_type [20];
    int idtype;
    int account_num;
    struct idnum
    {
        char aadhaar [15];
        char passport [15];
        char empcode [15];
    }id;
    char address [100];
}info;
struct Accommodation_Type
{ 
	int typeA[10];
	int typeB[10];
	int typeC[10];
	int typeD[10];
};
typedef struct union_tag{	
    union btree{		
        struct key_nodes{			
            unsigned long acc_no[m+1];			
            struct union_tag * ptr[m+1];			
            int count;		
            }key;		
            struct data_nodes{			
                info arr[DATA_SIZE+1];			
                struct union_tag * next;			
                struct union_tag * prev;			
                int dataCount;		
                }data;	
            }u;	
            char flag;
            }record;
            int validate_number(char str[]);
            int validate_name(char str[]);
            void printTree(record *root);
            record * searchNode(record *root, unsigned long no);
            void searchValueInDataNode(record *dptr, unsigned long val);
            void searchFunction(record *root,unsigned long val);
            int PushDown(unsigned long no, record *root, unsigned long *medno, record **right_subtree,info details);
            record * insert(record *root, info details, unsigned long no);
            void insertInDataNode(info details,record *root);
            void insertInKey(unsigned long no,record *root,record *right_subtree,int pos);
            void searchPosition(unsigned no,record *root,int *pos);
            void splitKey(unsigned long medentry,record *medright,record *root,int pos, unsigned long *newmedian,record **newright);void splitLeaf(info details,record *root,record **right_subtree,unsigned long *no);
            void update(info details,record *root,int i);
            //Function to validate phone number
            int validate_number(char str[])
            {	
                int len=strlen(str);	
                int flag=1;	int i;	
                if(len<=10)
                {
                    for(i=0;i<len && flag==1;i++)
                    {
                        int d=str[i];
                        if(!(d>=48 && d<=57))
                        {
                            flag=0;
                        }
                    }
                }
                else
                {
                    flag=0;
                }
                printf("********Flag:%d",flag);	
                return flag;
            }
            //Function to validate the name of Account holder.
            int validate_name(char str[])
            {	
                int i,l,flag=0;	
                l=strlen(str);	
                if(l>=25)	
                {		
                    printf("\nMaximum Characters allowed are 25\n");		
                    return 0;	
                }	
                for(i=0;i<l && flag==0;i++)	
                {		
                    if(str[i]<65 || str[i]>122)			
                        flag=1;		
                    else		
                    {			
                        if(str[i]>=91 && str[i]<=96)				
                        flag=1;		
                    }	
                }	
                return !flag;
            }//Function to make a record
            struct Accommodation_Type* allocate_block(char* acco_type,int acc,struct Accommodation_Type* accod)
            {
                int i;
                if(strcmp(acco_type,"A")==0)
                {
                    for(i=0;i<10;i++)
                    {
                        if(accod->typeA[i]==0)
                        {
                            accod->typeA[i]=acc;
                            break;
                        }
                    }
                }
                else if(strcmp(acco_type,"B")==0)
                {
                    for(i=0;i<10;i++)
                    {
                        if(accod->typeB[i]==0)
                        {
                            accod->typeB[i]=acc;
                            break;
                        }
                    }
                }
                else if(strcmp(acco_type,"C")==0)
                {
                    for(i=0;i<10;i++)
                    {
                        if(accod->typeC[i]==0)
                        {
                            accod->typeC[i]=acc;
                            break;
                        }
                    }
                }
                else if(strcmp(acco_type,"D")==0)
                {
                    for(i=0;i<10;i++)
                    {
                        if(accod->typeD[i]==0)
                        {
                            accod->typeD[i]=acc;
                            break;
                        }
                    }
                }
                return accod;
            }
            info makeRecord(char fname[],char lname[],char acco_type[],int idtyp,char idno[],char add[],struct Accommodation_Type* block)
            {	
                info details;	
                strcpy(details.firstname,fname);
                strcpy(details.lastname,lname);
                strcpy(details.accommodation_type,acco_type);
                details.idtype=idtyp;
                if(idtyp==0)
                {
                    strcpy(details.id.aadhaar,idno);
                    details.account_num=((pow(10,strlen(idno))*1)+atoi(idno));
                }
                else if(idtyp==1)
                {
                    strcpy(details.id.passport,idno);
                    details.account_num=((pow(10,strlen(idno))*2)+atoi(idno));
                }
                if(idtyp==2)
                {
                    strcpy(details.id.empcode,idno);
                    details.account_num=((pow(10,strlen(idno))*3)+atoi(idno));
                }	
                strcpy(details.address,add);
                block=allocate_block(acco_type,details.account_num,block);		
                return details;
            }
            //Function to print one record
            void printRecord(info rec)
            {			
                printf("------------------------------------------------------------------\n");			
                printf("Name: %s\t%s\n",rec.firstname,rec.lastname);			
                printf("Account number: %d\n",rec.account_num);
                if(rec.idtype==0)
                {
                    printf("Aadhar Number:%s",rec.id.aadhaar);
                }
                else if(rec.idtype==1)
                {
                    printf("Passport Number:%s",rec.id.passport);
                }	
                else if(rec.idtype==2)
                {
                    printf("Empcode Number:%s",rec.id.empcode);
                }	
                printf("\nAccomodation type: %s\n",rec.accommodation_type);
                printf("Address: %s\n",rec.address);						
                printf("------------------------------------------------------------------\n");
            }
            //Function which takes input from file and inserts it into tree.
            record * inputFromFile()
            {	
                FILE* fp;
                fp=fopen("read.txt","r"); 
                if(fp==NULL)
                {	
                    printf("NULL\n");	
                    
                }	
                else	
                {		
                    printf("File opened\n");	
                }
                char fname[100],buff[1000],lname[100],acc_typ[20];
                int acc_num,idno;
                char addr[1000];
                char idnu[16];
                char pno[15];
                info details;
                struct Accommodation_Type* blk;
                record *node=NULL;
                while(fscanf(fp,"%s",fname) && fscanf(fp,"%s",lname)!=EOF)
                {
                    fscanf(fp,"%s",buff);
                    acc_num=atoi(buff);
                    fscanf(fp,"%s",acc_typ);
                    fscanf(fp,"%s",buff);
                    idno=atoi(buff);
                    fscanf(fp,"%s",idnu);
                    fscanf(fp,"%s",addr);	
                    details=makeRecord(fname,lname,acc_typ,idno,idnu,addr,blk);
                    node=insert(node,details,details.account_num);	
                }	
                fclose(fp);	
                return node;
                }
                //Function which writes output into a file at the end of all operations
                void writeOutput(record *root)
                {	
                    FILE *fptr=fopen("output.txt","w");	
                    int i;		
                    if(root==NULL)	
                    {		
                        fprintf(fptr,"EMPTY\n");	
                    }	
                    else	
                    {			
                        record *tptr;		
                        info details;		
                        fprintf(fptr,"ACCOUNT_NAME\tACCOUNT NUMBER\tID Number\t\tAddress\t");		
                        while(root->flag=='k')		
                        {			
                            root=root->u.key.ptr[0];		
                        }		
                        if(root->flag=='d')		
                        {			
                            tptr=root;			
                            while(tptr!=NULL)			
                            {				
                                for(i=0;i<tptr->u.data.dataCount;i++)				
                                {					
                                    details=tptr->u.data.arr[i];					
                                    fprintf(fptr,"\n%s\t%s",details.firstname,details.lastname);
                                    fprintf(fptr,"\t\t%d",details.account_num);
                                    if(details.idtype==0)
                                    {
                                        fprintf(fptr,"\t\t%s",details.id.aadhaar);
                                    }
                                    if(details.idtype==1)
                                    {
                                        fprintf(fptr,"\t\t%s",details.id.passport);
                                    }
                                    if(details.idtype==2)
                                    {
                                        fprintf(fptr,"\t\t%s",details.id.empcode);
                                    }
                                    fprintf(fptr,"\t\t%s",details.address);						
                                }				
                                tptr=tptr->u.data.next;			
                            }					
                        }
                        fclose(fptr);		
                    }	
                }
                //Function to print the whole tree.
                void printTree(record *root)
                {	
                    int i;	
                    if(root==NULL)	
                    {		
                        printf("No records in the tree\n");	
                    }	
                    else if(root->flag=='d')	
                    {		
                        record *iptr;		
                        iptr=root;		
                        while(iptr!=NULL)		
                        {			
                            for(i=0;i<iptr->u.data.dataCount;i++)				
                            printRecord(iptr->u.data.arr[i]);			
                            printf("\n*****node ends*****\n");			
                            iptr=iptr->u.data.next;		
                        }	
                    }	
                    else	
                    {		
                        printTree(root->u.key.ptr[0]);	
                    }
                }
                //Function which searches a data node where required no could be present.
                //Returns a pointer to the data node for further inside search 
                record * searchNode(record *root, unsigned long no)
                {	
                    if(root->flag=='k')	
                    {		
                        int i=1;		
                        while(root->u.key.acc_no[i]<=no && i<=root->u.key.count)		
                        {			
                            i++;		
                        }		
                        root=searchNode(root->u.key.ptr[i-1],no);	
                    }	
                    return root;
                }
                //Searches for a particular value in data node and prints the details if value is present
                void searchValueInDataNode(record *dptr, unsigned long val)
                {	
                    int i;	
                    if(dptr==NULL)	
                    {		
                        printf("Error\n");	
                    }	
                    else if(dptr->flag=='d')	
                    {		
                        int found=0;		
                        for(i=0;i<DATA_SIZE && found==0;i++)		
                        {			
                            if(dptr->u.data.arr[i].account_num==val)			
                            {				
                                found=1;			
                            }		
                        }		
                        if(found==0)		
                        {			
                            printf("KEY NOT FOUND\n");		
                        }		
                        else		
                        {			
                            printf("The details of record are: \n");			
                            printf("Name: %s\t%s\n",dptr->u.data.arr[i-1].firstname,dptr->u.data.arr[i-1].lastname);			
                            printf("Account number: %lu\n",dptr->u.data.arr[i-1].account_num);
                            if(dptr->u.data.arr[i-1].idtype==0)
                            {
                                printf("Aadhar Number:%s",dptr->u.data.arr[i-1].id.aadhaar);
                            }
                            else if(dptr->u.data.arr[i-1].idtype==1)
                            {
                                printf("Aadhar Number:%s",dptr->u.data.arr[i-1].id.passport);
                            }	
                            else if(dptr->u.data.arr[i-1].idtype==2)
                            {
                                printf("Aadhar Number:%s",dptr->u.data.arr[i-1].id.empcode);
                            }	

                            printf("Address: %s\n",dptr->u.data.arr[i-1].address);					
                            printf("************************************************************");		
                        }	
                    }
                }
                //Actual Search function
                void searchFunction(record *root,unsigned long val)
                {	
                    record *result;	
                    result=searchNode(root,val);	
                    searchValueInDataNode(result,val);
                }
                //Recursive helper function in insert
                int PushDown(unsigned long no, record *root, unsigned long *medno, record **right_subtree,info details)
                {	
                    int pos,i=0;	
                    int found=0;	
                    //Stopping condition of recursion	
                    if(root->flag=='d')	
                    {		
                        //Move forward till you encounter a node having equal or greater value than the required acc no		
                        while(root->u.data.arr[i].account_num<no && i<root->u.data.dataCount)		
                        {			
                            i++;		
                        }		
                        //If the value is same as the one to be inserted, we update that record with the new fields.		
                        if(root->u.data.arr[i].account_num==no)		
                        {			
                            update(details,root,i);		
                        }		
                        //If the value is greater we insert it taking into cosideration the node capacity		
                        else		
                        {			
                            //If the node where data is to be inserted has less than maximum elements, we simply insert and we are done.		
                            if(root->u.data.dataCount<DATA_SIZE)			
                            {				
                                insertInDataNode(details,root);				
                                return 0;			
                            } 			
                            //If data node is already full, we have to split it into two and continue the recursion as it will affecthe above levels			
                            else			
                            {				
                                splitLeaf(details,root,right_subtree,medno);				
                                return 1;			
                            }		
                        }	
                    }	
                    else if(root->flag=='k')	
                    {		
                        //We search for a position to move the pointer in order to reach a particular node		
                        searchPosition(no,root,&pos);		
                        //if the recursion is to be continued. The case when data node has been splitted into two.		
                        if(PushDown(no,root->u.key.ptr[pos], medno,right_subtree,details))		
                        {			
                            //Splitleaf sends a median which is to be inserted in key nodes, we assign it to no.		    
                            no=*medno;		
                            //If the key node where median is to be inserted has less than maximum node, we simply insert the key and we are done.			
                            if(root->u.key.count<MAX)			
                            {				
                                insertInKey(no,root,*right_subtree,pos);				
                                return 0;		
                            }			
                            //If the key node has maximum number of nodes, we split the key node and continue the recursion for inserting keys in further levels.			
                            else			
                            {				
                                splitKey(no,*right_subtree,root,pos,medno,right_subtree);				
                                return 1;			
                            }		
                        }		
                        return 0;	
                    }
                }
                record * insert(record *root, info details, unsigned long no)
                {	
                    unsigned long medno;	
                    record * right_subtree;	
                    record * newroot;	
                    //The very first node which will be inserted is a data node and created explicitly.	
                    if(root==NULL)	
                    {		
                        record *nptr;		
                        nptr=(record *)malloc(sizeof(record));		
                        nptr->flag='d';		
                        nptr->u.data.arr[0]=details;		
                        nptr->u.data.dataCount=1;		
                        nptr->u.data.next=NULL;		
                        nptr->u.data.prev=NULL;		
                        root=nptr;		
                        NumRecords++;	
                    }	
                    //For all other nodes we call the recursive function	
                    else if(PushDown(no,root,&medno,&right_subtree,details))	
                    {		
                        //The actual root of the tree is created here. Pushdown send the median to be inserted and the right and left subtrees to be attached.		
                        newroot=(record *)malloc(sizeof(record));		
                        newroot->flag='k';		
                        newroot->u.key.count=1;		
                        newroot->u.key.acc_no[1]=medno;		
                        newroot->u.key.ptr[0]=root;		
                        newroot->u.key.ptr[1]=right_subtree;		
                        return newroot;	
                    }	
                    return root;
                }
                //Function which shifts the entries in the data node and inserts the acc_no at desired position
                void insertInDataNode(info details,record *root)
                {	
                    int i=root->u.data.dataCount-1;	
                    if(root->flag=='d')	
                    {		
                        while(root->u.data.arr[i].account_num>=details.account_num && i>=0)		
                        {			
                            root->u.data.arr[i+1]=root->u.data.arr[i];			
                            i--;		
                        }		
                        root->u.data.arr[i+1]=details;	
                    }	
                    root->u.data.dataCount++;	
                    NumRecords++;
                }
                //Function which shifts the entries and pointer in the key node and inserts the acc_no at desired position and its right subtree at its appropriate position
                void insertInKey(unsigned long no,record *root,record *right_subtree,int pos)
                {	
                    int i;	
                    for(i=root->u.key.count;i>pos;i--)	
                    {		
                        root->u.key.acc_no[i+1]=root->u.key.acc_no[i];		
                        root->u.key.ptr[i+1]=root->u.key.ptr[i];	
                    }	
                    root->u.key.acc_no[pos+1]=no;	
                    root->u.key.ptr[pos+1]=right_subtree;	
                    root->u.key.count++;
                }
                //Function which gives the position of the branch which ultimately leads to the data node where the entry could be present
                void searchPosition(unsigned no,record *root,int *pos)
                {	
                    if(root->flag=='k')	
                    {		
                        if(no<root->u.key.acc_no[1])		
                        {			
                            *pos=0;	
                        }		
                        else		
                        {			
                            for(*pos=root->u.key.count;no<root->u.key.acc_no[*pos];*pos=*pos-1);		
                        }	
                    }
                }
                //Function which splits the key nodes and sends the median and right and left subtree of the median
                void splitKey(unsigned long medentry,record *medright,record *root,int pos, unsigned long *newmedian,record **newright){	
                    int i;	
                    int median;	
                    //We find the correct position of the median	
                    if(pos<=MIN)	
                    {		
                        median=MIN;	
                    }	
                    else	
                    {		
                        median=MIN+1;	
                    }	
                    //New node to act as a right node	
                    *newright=(record *)malloc(sizeof(record));	
                    //All the elements after median in original node are copied into the right subtree	
                    for(i=median+1;i<=MAX;i++)	
                    {		
                        (*newright)->u.key.acc_no[i-median]=root->u.key.acc_no[i];		
                        (*newright)->u.key.ptr[i-median]=root->u.key.ptr[i];	
                    }	
                    //Counts in both the nodes are set appropriately	
                    (*newright)->flag='k';	
                    (*newright)->u.key.count=MAX-median;	
                    root->u.key.count=median;	
                    if(pos<=MIN)	
                    {		
                        insertInKey(medentry,root,medright,pos);	
                    }	
                    else	
                    {		
                        insertInKey(medentry,*newright,medright,pos-median);	
                    }	
                    *newmedian=root->u.key.acc_no[root->u.key.count];	
                    (*newright)->u.key.ptr[0]=root->u.key.ptr[root->u.key.count];	
                    root->u.key.count--;
                }
                //Function which splits the data node
                void splitLeaf(info details,record *root,record **right_subtree,unsigned long *no)
                {
                    info temp_arr[m+1];
                    record *leaf_right;
                    int i=0,j,k=0;
                    //Copy all the record in a temporary array along with the one to be inserted      
                    while(details.account_num>root->u.data.arr[i].account_num && i<root->u.data.dataCount)
                    { 
                        temp_arr[i]=root->u.data.arr[i];
                        i++;
                    }
                    temp_arr[i]=details;
                    while(i<=root->u.data.dataCount)
                    {
                        temp_arr[i+1]=root->u.data.arr[i];
                        i++;
                    }
                    *no=temp_arr[i/2].account_num;
                    root->u.data.dataCount=(int)ceil((double)root->u.data.dataCount/2);
                    leaf_right=(record *)malloc(sizeof(record));
                    leaf_right->flag='d';
                    leaf_right->u.data.dataCount=i-root->u.data.dataCount;
                    for(j=0;j<i/2;j++)
                    {
                        root->u.data.arr[j]=temp_arr[j];
                    }
                    for(j=i/2;j<i;j++)
                    {
                        leaf_right->u.data.arr[k]=temp_arr[j];
                        k++;
                    }
                    if(root->u.data.next!=NULL)
                    { 	
                        (root->u.data.next)->u.data.prev=leaf_right;	 
                    }
                    leaf_right->u.data.next=root->u.data.next;
                    root->u.data.next=leaf_right;
                    leaf_right->u.data.prev=root;
                    *right_subtree=leaf_right;
                    NumRecords++;
                }
                void update(info details,record *root,int i)
                {	
                    root->u.data.arr[i]=details;
                }
                void MoveLeftKey(record *root,int pos)
                {	
                    int c;	record *t;	
                    t=root->u.key.ptr[pos-1];	
                    t->u.key.count++;	
                    t->u.key.acc_no[t->u.key.count]=root->u.key.acc_no[pos];	
                    t->u.key.ptr[t->u.key.count]=(root->u.key.ptr[pos])->u.key.ptr[0];	
                    t=root->u.key.ptr[pos];	root->u.key.acc_no[pos]=t->u.key.acc_no[1];	
                    t->u.key.ptr[0]=t->u.key.ptr[1];	
                    t->u.key.count--;	
                    for(c=1;c<=t->u.key.count;c++)	
                    {		
                        t->u.key.acc_no[c]=t->u.key.acc_no[c+1];		
                        t->u.key.ptr[c]=t->u.key.ptr[c+1];	
                    }
                }
                void MoveRightKey(record *root,int pos)
                {	
                    int c;	
                    record *t;	
                    t=root->u.key.ptr[pos];	
                    for(c=t->u.key.count;c>0;c--)	
                    {		
                        t->u.key.acc_no[c+1]=t->u.key.acc_no[c];		
                        t->u.key.ptr[c+1]=t->u.key.ptr[c];	
                    }	
                    t->u.key.ptr[1]=t->u.key.ptr[0];	
                    t->u.key.count++;	
                    t->u.key.acc_no[1]=root->u.key.acc_no[pos];	
                    t=root->u.key.ptr[pos-1];	
                    root->u.key.acc_no[pos]=t->u.key.acc_no[t->u.key.count];	
                    (root->u.key.ptr[pos])->u.key.ptr[0]=t->u.key.ptr[t->u.key.count];	
                    t->u.key.count--;
                }
                void CombineKey(record *root,int pos)
                {	
                    int c;	
                    record * right, * left;	
                    right=root->u.key.ptr[pos];	
                    left=root->u.key.ptr[pos-1];	
                    left->u.key.count++;		
                    left->u.key.acc_no[left->u.key.count]=root->u.key.acc_no[pos];	
                    left->u.key.ptr[left->u.key.count]=right->u.key.ptr[0];		
                    for(c=1;c<=right->u.key.count;c++)	
                    {		
                        left->u.key.count++;		
                        left->u.key.acc_no[left->u.key.count]=right->u.key.acc_no[c];		
                        left->u.key.ptr[left->u.key.count]=right->u.key.ptr[c];	
                    }		
                    for(c=pos;c<root->u.key.count;c++)	
                    {		
                        root->u.key.acc_no[c]=root->u.key.acc_no[c+1];		
                        root->u.key.ptr[c]=root->u.key.ptr[c+1];	
                    }		
                    root->u.key.count--;	
                    free(right);		
                }
                void MoveLeftLeaf(record *root,int pos)
                {	
                    record *lhs;	
                    record *rhs;	
                    int c;	
                    lhs=root->u.key.ptr[pos-1];	
                    rhs=root->u.key.ptr[pos];	
                    lhs->u.data.arr[lhs->u.data.dataCount]=rhs->u.data.arr[0];	
                    lhs->u.data.dataCount++;	
                    root->u.key.acc_no[pos]=rhs->u.data.arr[1].account_num;	
                    for(c=1;c<rhs->u.data.dataCount;c++)	
                    {		
                        rhs->u.data.arr[c-1]=rhs->u.data.arr[c];			
                    }	
                    rhs->u.data.dataCount--;
                }
                void MoveRightLeaf(record *root,int pos)
                {	
                    record *lhs;	
                    record *rhs;	
                    int c;	
                    lhs=root->u.key.ptr[pos-1];	
                    rhs=root->u.key.ptr[pos];	
                    for(c=rhs->u.data.dataCount-1;c>=0;c--)	
                    {		
                        rhs->u.data.arr[c+1]=rhs->u.data.arr[c];	
                    }	
                    rhs->u.data.dataCount++;	
                    rhs->u.data.arr[0]=lhs->u.data.arr[lhs->u.data.dataCount-1];	
                    root->u.key.acc_no[pos]=rhs->u.data.arr[lhs->u.data.dataCount-1].account_num;	
                    lhs->u.data.dataCount--;	
                }
                void CombineLeaf(record *root,int pos)
                {	
                    record *lhs,*rhs;	
                    int c;	
                    lhs=root->u.key.ptr[pos-1];	
                    rhs=root->u.key.ptr[pos];	
                    int elems=lhs->u.data.dataCount;	
                    for(c=0;c<rhs->u.data.dataCount;c++)	
                    {			
                        lhs->u.data.arr[elems]=rhs->u.data.arr[c];		
                        elems++;	
                    }	
                    for(c=pos+1;c<=root->u.key.count;c++)	
                    {		
                        root->u.key.acc_no[c-1]=root->u.key.acc_no[c];		
                        root->u.key.ptr[c-1]=root->u.key.ptr[c];	
                    }	
                    lhs->u.data.next=rhs->u.data.next;	
                    if(rhs->u.data.next!=NULL)	
                    {		
                        (rhs->u.data.next)->u.data.prev=lhs;	
                    }	
                    lhs->u.data.dataCount=elems;	
                    root->u.key.count--;	
                    free(rhs);	
                }
                void DeleteFromLeafDirect(unsigned long target,record *root)
                {	
                    int pos,i=0;	
                    if(root->flag=='d')	
                    {		
                        while(root->u.data.arr[i].account_num<target)		
                        {			
                            i++;		
                        }		
                        if(root->u.data.arr[i].account_num>target)		
                        {			
                            printf("ENTRY TO BE DELETED IS ABSENT\n");		
                        }		
                        else if(root->u.data.arr[i].account_num==target)		
                        {			
                            i++;			
                            for(i;i<root->u.data.dataCount;i++)			
                            {				
                                root->u.data.arr[i-1]=root->u.data.arr[i];			
                            }			
                            root->u.data.dataCount--;		
                        }	
                    }	
                    NumRecords--;
                }
                //Pos is always the right node
                int RestoreLeaf(unsigned long target,record *root,int pos)
                {	
                    int k=0;	
                    int retval=0;	
                    if(pos==0)	
                    {		
                        if((root->u.key.ptr[1])->u.data.dataCount>MIN_DATASIZE)		
                        {			
                            MoveLeftLeaf(root,1);		
                        }		
                        else		
                        {			
                            CombineLeaf(root,1);			
                            retval=1;	
                        }	
                    }	
                    else if(pos==root->u.key.count)	
                    {		
                        if((root->u.key.ptr[pos-1])->u.data.dataCount>MIN_DATASIZE)		
                        {			
                            MoveRightLeaf(root,pos);		
                        }		
                        else		
                        {			
                            CombineLeaf(root,pos);			
                            retval=1;		
                        }	
                    }	
                    else if((root->u.key.ptr[pos-1])->u.data.dataCount>MIN_DATASIZE)	
                    {		
                        MoveRightLeaf(root,pos);	
                    }	
                    else if((root->u.key.ptr[pos+1])->u.data.dataCount>MIN_DATASIZE)	
                    {		
                        MoveLeftLeaf(root,pos+1);	
                    }	
                    else	
                    {		
                        CombineLeaf(root,pos);		
                        retval=1;	
                    }	
                    return retval;	
                }
                int RestoreKey(unsigned long target,record *root,int pos)
                {	
                    int k=0;	
                    int retval=0;	
                    if(pos==0)	
                    {		
                        if((root->u.key.ptr[1])->u.key.count>MIN)		
                        {			
                            MoveLeftKey(root,1);		
                        }		
                        else		
                        {			
                            CombineKey(root,1);			
                            retval=1;		
                        }	
                    }	
                    else if(pos==root->u.key.count)	
                    {		
                        if((root->u.key.ptr[pos-1])->u.key.count>MIN)		
                        {			
                            MoveRightKey(root,pos);		
                        }		
                        else		
                        {			
                            CombineKey(root,pos);			
                            retval=1;		
                        }	
                    }	
                    else if((root->u.key.ptr[pos-1])->u.key.count>MIN)	
                    {		
                        MoveRightKey(root,pos);	
                    }	
                    else if((root->u.key.ptr[pos+1])->u.key.count>MIN)	
                    {		
                        MoveLeftKey(root,pos+1);	
                    }	
                    else	
                    {		
                        CombineKey(root,pos);		
                        retval=1;	
                    }	
                    return retval;
                }
                int Delete_rec(unsigned long target,record *root)
                {	
                    int pos,k,check_count;	
                    if((root->u.key.ptr[0])->flag=='d')	
                    {		
                        searchPosition(target,root,&pos);		
                        DeleteFromLeafDirect(target,root->u.key.ptr[pos]);		
                        check_count=(root->u.key.ptr[pos])->u.data.dataCount;		
                        if(check_count>=MIN_DATASIZE)		
                        {			
                            return 0;		
                        }		
                        else		
                        {			
                            k=RestoreLeaf(target,root,pos);		
                        //returns 1 if merge else 0			
                            return k;				
                        }			
                    }	
                    else	
                    {		
                        searchPosition(target,root,&pos);		
                        if(Delete_rec(target,root->u.key.ptr[pos]))		
                        {			
                            check_count=(root->u.key.ptr[pos])->u.key.count;			
                            if(check_count>=MIN)			
                            {				
                                return 0;			
                            }			
                            else			
                            {				
                                k=RestoreKey(target,root,pos);				
                                return k;			
                            }					
                        }					
                    }	
                    return 0;
                }
                record * Delete(unsigned long target,record *root)
                {	
                    record *oldroot;	
                    int k;	
                    if(root==NULL)	
                    {		
                        printf("Tree is empty\n");	
                    }	
                    else if(root->flag=='d')	
                    {		
                        DeleteFromLeafDirect(target,root);	
                    }	
                    else if (root->flag=='k')	
                    {		
                        Delete_rec(target,root);		
                        if(root->u.key.count==0)		
                        {			
                            oldroot=root;			
                            root=root->u.key.ptr[0];			
                            free(oldroot);		
                        }	
                    }		
                    return root;
                }
                void getNum(record *root)
                {	
                    printf("The number of records in the database are %d\n",NumRecords);
                }
                int Height(record *root)
                {	
                    int retval;	
                    if(root==NULL)	
                    {		
                        retval=-1;	
                    }	
                    else if(root->flag=='d')	
                    {		
                        retval=0;	
                    }	
                    else	
                    {		
                        retval=1+Height(root->u.key.ptr[0]);	
                    }	
                    return retval;
                }
                void RangeSearch(record *root, unsigned int key1, unsigned int key2)
                {	
                    record *node,*sptr;	int found=0,i;		
                    if(root==NULL)	
                    {		
                        printf("Tree is empty\n");	
                    }	
                    else	
                    {		
                        node=searchNode(root,key1);		
                        sptr=node;		
                        printf("The details of record are: \n");		
                        while(sptr!=NULL && found==0)		
                        {			
                            for(i=0;i<sptr->u.data.dataCount && found==0;i++)			
                            {				
                                if(sptr->u.data.arr[i].account_num>=key1 && sptr->u.data.arr[i].account_num<=key2)				{					
                                    printRecord(sptr->u.data.arr[i]);				
                                }				
                                if(sptr->u.data.arr[i].account_num>=key2)				
                                {					
                                    found=1;			
                                }				
                            }			
                            sptr=sptr->u.data.next;		
                        }		
                        if(found==0)		
                        {			
                            printf("No records in the given range\n");		
                        }	
                    }
                }
                //Function which allocates block to the user allocated has the account number of user deallocated are 0
                struct Accommodation_Type* specialRequestAllocation(struct Accommodation_Type* accommo, record* root)
                {
                    int i,j,block,id,found=0;
                    char str[30],accod[30];
                    record* temp;
                    
                    printf("Enter Account Number");
                    scanf("%d",&id);
                    temp=searchNode(root,id);
                    printf("Enter Accommodation type(A/B/C/D) & block to be allocated");
                    scanf("%s",accod);
                    scanf("%d",&block);
                    if(temp==NULL)
                    {
                        printf("User not found.");
                        return NULL;
                    }
                    else
                    {
                        while(temp!=NULL)		
                        {			
                            for(i=0;i<temp->u.data.dataCount && found==0;i++)			
                            {				
                                if(temp->u.data.arr[i].account_num==id)
                                {					
                                    strcpy(temp->u.data.arr[i].accommodation_type,accod);
                                    break; 				
                                }							
                            }			
                            temp=temp->u.data.next;		
                        }
                    }   		
                    
                    if(strcmp(accod,"A")==0)
                    {
                        
                        if(accommo->typeA[block]==0)
                        {
                            printf("Avaible & allocated");
                            accommo->typeA[block]=id;
                                    
                        }
                        else
                        {
                            printf("Not available");
                        }
                            
                    }
                    else if(strcmp(accod,"B")==0)
                    {
                        if(accommo->typeB[block]==0)
                        {
                            printf("Avaible & allocated");
                            accommo->typeB[block]=id;
                                
                        }
                        else
                        {
                            printf("Not available");
                        }
                    }
                    else if(strcmp(accod,"C")==0)
                    {
                        if(accommo->typeC[block]==0)
                        {
                            printf("Avaible & allocated");
                            accommo->typeC[block]=id;
                                
                        }
                        else
                        {
                            printf("Not available");
                        }
                    }
                    else if(strcmp(accod,"D")==0)
                    {
                        if(accommo->typeD[block]==0)
                        {
                            printf("Avaible & allocated");
                            accommo->typeD[block]=id;
                                
                        }
                        else
                        {
                            printf("Not available");
                        }
                    }
                    return accommo;

                }
                void addressSearch(struct Accommodation_Type* blk,record* root,char type[],int start, int end)
                {
                    int i;
                    
                    if(strcmp(type,"A")==0)
                    {
                        for(i=start;i<=end;i++)
                        {
                            if(blk->typeA[i]!=0)
                            {
                                printf("\nResident in block %d:",i);
                                searchFunction(root,blk->typeA[i]);
                            }
                        }
                    } 
                    else if(strcmp(type,"B")==0)
                    {
                        for(i=start;i<=end;i++)
                        {
                            if(blk->typeB[i]!=0)
                            {
                                printf("\nResident in block %d:",i);
                                searchFunction(root,blk->typeB[i]);
                            }
                        }
                    } 
                    else if(strcmp(type,"C")==0)
                    {
                        for(i=start;i<=end;i++)
                        {
                            if(blk->typeC[i]!=0)
                            {
                                printf("\nResident in block %d:",i);
                                searchFunction(root,blk->typeC[i]);
                            }
                        }
                    }
                    else if(strcmp(type,"D")==0)
                    {
                        for(i=start;i<=end;i++)
                        {
                            if(blk->typeD[i]!=0)
                            {
                                printf("\nResident in block %d:",i);
                                searchFunction(root,blk->typeD[i]);
                            }
                        }
                    } 


                }
                void update_id(record* root,int idnum,int acc_no)
                {
                    char uptd[16];
                    int i;
                    record* temp=root;
                    if(idnum==0)
                    {
                        printf("Enter aadhar no. to be updated");
                        scanf("%s",uptd);
                        while(temp!=NULL)		
                        {			
                            for(i=0;i<temp->u.data.dataCount;i++)			
                            {				
                                if(temp->u.data.arr[i].account_num==acc_no)
                                {
                                    temp->u.data.arr[i].idtype=0;
                                    strcpy(temp->u.data.arr[i].id.aadhaar,uptd);				
                                    break; 				
                                }							
                            }			
                            temp=temp->u.data.next;		
                        }
                    }    			
                    else if(idnum==1)
                    {
                        printf("Enter passport no. to be updated");
                        scanf("%s",uptd);
                        while(temp!=NULL)		
                        {			
                            for(i=0;i<temp->u.data.dataCount;i++)			
                            {				
                                if(temp->u.data.arr[i].account_num==acc_no)
                                {
                                    temp->u.data.arr[i].idtype=1;
                                    strcpy(temp->u.data.arr[i].id.passport,uptd);				
                                    break; 				
                                }							
                            }			
                            temp=temp->u.data.next;		
                        }			
                    }    
                    else if(idnum==2)
                    {
                        printf("Enter aadhar no. to be updated");
                        scanf("%s",uptd);
                        while(temp!=NULL)		
                        {			
                            for(i=0;i<temp->u.data.dataCount;i++)			
                            {				
                                if(temp->u.data.arr[i].account_num==acc_no)
                                {
                                    temp->u.data.arr[i].idtype=2;
                                    strcpy(temp->u.data.arr[i].id.empcode,uptd);				
                                    break; 				
                                }							
                            }			
                             temp=temp->u.data.next;		
                        }			
                                    
                    }    	
                }
                void Update(record* root,int acc_no)
                {
                    int choice,i,j,idnu,pos;
                    char uptd[20];
                    record* temp=root;
                    record* temp2;
                    if (root == NULL)
                    {
                        printf("Node is empty returning null\n");
                        return;
                    }
                    
                    
                    printf("\n1. firstname \n 2. lastname \n3. accommodation type \n4. idtype && idnum \n5. address");
                    printf("Enter choice to be updated");
                    scanf("%d",&choice);
                    switch(choice)
                    {
                    
                        case 1: printf("Enter first-name to be updated");
                                scanf("%s",uptd);
                                while(temp!=NULL)		
                                {			
                                    for(i=0;i<temp->u.data.dataCount;i++)			
                                    {				
                                        if(temp->u.data.arr[i].account_num==acc_no)
                                        {
                                            strcpy(temp->u.data.arr[i].firstname,uptd);					
                                            break; 				
                                        }							
                                    }			
                                    temp=temp->u.data.next;		
                                }				
                                
                                break; 				
            
                                break;
                        case 2: printf("Enter last-name to be updated");
                                scanf("%s",uptd);
                                while(temp!=NULL)		
                                {			
                                    for(i=0;i<temp->u.data.dataCount;i++)			
                                    {				
                                        if(temp->u.data.arr[i].account_num==acc_no)
                                        {
                                            strcpy(temp->u.data.arr[i].lastname,uptd);					
                                            break; 				
                                        }							
                                    }			
                                    temp=temp->u.data.next;		
                                }			
                                
                                break;
                        case 3: printf("Enter accomodation type to be updated");
                                scanf("%s",uptd);
                                while(temp!=NULL)		
                                {			
                                    for(i=0;i<temp->u.data.dataCount;i++)			
                                    {				
                                        if(temp->u.data.arr[i].account_num==acc_no)
                                        {
                                            strcpy(temp2->u.data.arr[i].accommodation_type,uptd);					
                                            break; 				
                                        }							
                                    }			
                                    temp=temp->u.data.next;		
                                }			
                                
                                break;
                        case 4: printf("Enter id-type to be updated");
                                scanf("%d",idnu);
                                update_id(root,idnu,acc_no);
                                break;
                        case 5: printf("Enter address to be updated");
                                scanf("%s",uptd);
                                while(temp!=NULL)		
                                {			
                                    for(i=0;i<temp->u.data.dataCount;i++)			
                                    {				
                                        if(temp->u.data.arr[i].account_num==acc_no)
                                        {
                                                
                                            strcpy(temp->u.data.arr[i].address,uptd);				
                                            break; 				
                                        }							
                                    }			
                                    temp=temp->u.data.next;		
                                }			
                                
                                break;
                    }
                }
                struct Accommodation_Type* deallocate_block(struct Accommodation_Type* blk,int acc_no,record* root)
                {
                    record* temp=root;
                    int i;
                    char t[1];
                    while(temp!=NULL)		
                    {			
                        for(i=0;i<temp->u.data.dataCount;i++)			
                        {				
                            if(temp->u.data.arr[i].account_num==acc_no)
                            {
                                strcpy(t,temp->u.data.arr[i].address);				
                                break; 				
                            }							
                        }			
                        temp=temp->u.data.next;		
                    }
                    if(strcmp(t,"A")==0)
                    {
                        for(i=0;i<10;i++)
                        {
                            if(blk->typeA[i]==acc_no)
                            {
                                blk->typeA[i]=0;
                                break;
                            }
                        }
                    }
                    else if(strcmp(t,"B")==0)
                    {
                        for(i=0;i<10;i++)
                        {
                            if(blk->typeB[i]==acc_no)
                            {
                                blk->typeB[i]=0;
                                break;
                            }
                        }
                    }
                    else if(strcmp(t,"C")==0)
                    {
                        for(i=0;i<10;i++)
                        {
                            if(blk->typeC[i]==acc_no)
                            {
                                blk->typeC[i]=0;
                                break;
                            }
                        }
                    }
                    else if(strcmp(t,"D")==0)
                    {
                        for(i=0;i<10;i++)
                        {
                            if(blk->typeD[i]==acc_no)
                            {
                                blk->typeD[i]=0;
                                break;
                            }
                        }
                    }
                    return blk;				

                    
                }



                int main()
                {	int choice,i;
                    char fname[100],address[100],idno[15],lname[100],acco_typ[20];
                    int idnum,acc_no;
                    record *root=NULL;
                    struct Accommodation_Type* block=malloc(sizeof(struct Accommodation_Type));
                    int start,end;
                    char type[1];
                    for(i=0;i<10;i++)
                    {
                        block->typeA[i]=0;
                        block->typeB[i]=0;
                        block->typeC[i]=0;
                        block->typeD[i]=0;
                    }
                    int key1,key2,h,before,after;
                    char enter;
                    info details;
                    root=inputFromFile();
                    do{
                        printf("------------------------------------------------------------\n");		
                        printf("MENU\n");		
                        printf("0:PRINT LIST\n");		
                        printf("1:INSERT DATA\n");		
                        printf("2:DELETE DATA\n");		
                        printf("3:GET NUMBER OF ACTIVE RECORD\n");		
                        printf("4:SEARCH\n");		
                        printf("5.HEIGHT OF THE TREE\n");		
                        printf("6.RANGE SEARCH\n");
                        printf("7:SPECIAL REQUEST ALLOCATION\n");
                        printf("8:UPDATE INFO\n");
                        printf("9:ALLOCATED BLOCKS\n");
                        printf("10:QUIT OUTPUT RECORD\n");		
                        printf("------------------------------------------------------------\n");		
                        scanf("%d",&choice);		
                        switch(choice)		
                        {			
                            case 0: 
                                printf("The data in the tree is:\n");					
                                printTree(root);					
                                break;			
                                    
                            case 1: 
                                printf("Enter account holder's name\n");		
                                scanf("%s",fname);		 
                                scanf("%s",lname);
                                printf("Enter accommmodation type(A/B/C/D)\n");		
                                scanf("%s",acco_typ);		 
                                printf("Enter id number\n");		
                                scanf("%d",&idnum);
                                printf("Enter (Aadhar/passport/empcode) number\n");		 
                                scanf("%s",idno);		
                                printf("Enter address\n");		
                                scanf("%s",address);	
                                details=makeRecord(fname,lname,acco_typ,idnum,idno,address,block);
                                before=NumRecords;	
                                root=insert(root,details,details.account_num);	
                                after=NumRecords;
                                if(before<after) 
                                {
                                    printf("INSERTED SUCCESSFULLY\n");					
                                }					
                                else					
                                {						
                                    printf("INSERTION UNSUCCESSFUL\n");					
                                }	 
                                printf("Tree after insertion\n");	 
                                printTree(root);		
                                break;

                            case 2: 
                                printf("Enter the account number to be deleted\n");					
                                scanf("%d",&acc_no);
                                block=deallocate_block(block,acc_no,root);					
                                before=NumRecords;					
                                root=Delete(acc_no,root);					
                                after=NumRecords;					
                                if(before>after)	
                                {	
                                    printf("DELETED SUCCESSFULLY\n");					
                                }					
                                else					
                                {						
                                    printf("DELETION UNSUCCESSFUL\n");					
                                }					
                                printf("Tree after deletion\n");
                                printTree(root);		
                                break;
                            case 3:	
                                getNum(root);				
                                break;		
                            case 4: 
                                printf("Enter the account number to be searched\n");		 		
                                scanf("%lu",&acc_no);	 		
                                searchFunction(root,acc_no);			
                                break;	 
                            case 5: 
                                h=Height(root);		
                                printf("Height of the tree is %d\n",h);	 		
                                break;		 
                            case 6: 
                                printf("Enter the lower and upper limits\n");		 		
                                scanf("%lu %lu",&key1,&key2);		 		
                                RangeSearch(root,key1,key2);		 		
                                break;		
                            case 7:
                                printf("Special Block request allocation");
                                specialRequestAllocation(block,root);
                                break;
                                
                            case 8:
                                printf("Enter the account number to be updated\n");		 		
                                scanf("%d",&acc_no);
                                Update(root,acc_no);
                                break;
                                
                            case 9:
                                
                                printf("\nEnter block to be printed");
                                scanf("%s",type);
                                printf("\nEnter the range of blocks(1-10)");
                                scanf("%d",&start);
                                scanf("%d",&end);
                                printf("Allocated blocks:");
                                addressSearch(block,root,type,start,end);
                                break;
                            case 10:
                                printf("THANK YOU\n");			
                                writeOutput(root);	 		
                                break;
                                
                            default: 
                                printf("Invalid entry\n");	 		
                                break;											
                        }
                        	
                    
                }while(choice>=0 && choice<=10);
                return 0;
            }    
