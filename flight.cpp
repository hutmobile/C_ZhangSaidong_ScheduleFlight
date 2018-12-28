#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define infinity 32767
#define maxsize 50

typedef struct
{
    int stack[maxsize];
    int top;
}SeqStack;


typedef struct arcnode//�ڽӱ�ṹ��
{
    char routename[20];/*������*/
    int serialnum;/*��һվ�������*/
    int timelength;/*��������ʱ��(��),�����ʱ����ΪȨ��*/
    struct arcnode *next;
}anode;

typedef struct vertexnode
{
    int visit;/*���ʱ�־*/
    int in;/*���*/
    int out;/*����*/
    char airportname[20];/*��������*/
    char safelevel[10];/*������ȫϵ��*/
    char narration[100];/*��������*/
    anode *head;
}vnode;

typedef struct
{
    vnode vertex[maxsize];
    int portnum;/*������*/
    int airlinenum;/*������*/
}adjlist;



typedef struct
{
    int routes[maxsize][maxsize];
    int portnum;//������
    char airpotname[maxsize][100];//��������
}adjmartrix;



void establish(adjlist *a)//�Ѵ�����ͼд���ļ����ŵ�creategraph(adjlist *a)��
{
    int i,j;
    anode *p;
    
    FILE *sfp,*rfp;
    sfp=fopen("air.txt","wt");//�����»����ļ�
    rfp=fopen("route.txt","wt");
    fprintf(sfp,"%d %d\n",a->portnum,a->airlinenum);/*�������ͺ�����д��air��*/
    for(i=1;i<=a->portnum;i++)
        fprintf(sfp,"%s %s %s %d %d\n",a->vertex[i].airportname,a->vertex[i].safelevel,a->vertex[i].narration,a->vertex[i].out,a->vertex[i].in);
    for(i=1;i<=a->portnum;i++)/*������Ϣд��route��*/
    {
        p=a->vertex[i].head;
        if(a->vertex[i].out!=0)
        {
            fprintf(rfp,"%s %d %d\n",p->routename,p->serialnum,p->timelength);
            p=p->next;
        }
        for(j=1;j<a->vertex[i].out;j++)
        {
            fprintf(rfp,"%s %d %d\n",p->routename,p->serialnum,p->timelength);
            p=p->next;
        }
    }
    fclose(sfp);//�ر��ļ�
    fclose(rfp);//�ر��ļ�
}




void churudu(adjlist *a)/*������Ⱥ����*/
{
    int i,n;
    anode *p;
    for(i=1;i<=a->portnum;i++)/*�������*///����
    {
        p=a->vertex[i].head;
        if(p!=NULL)
        {
            n=1;
            p=p->next;
        }
        else
            n=0;
        while(p!=NULL)
        {
            n++;
            p=p->next;
        }
        a->vertex[i].out=n;
    }
    for(i=1;i<=a->portnum;i++)
        a->vertex[i].in=0;/*�ڵ���churudu()֮ǰ��ԭ�л�����ȱ�Ϊ0*/
    for(i=1;i<=a->portnum;i++)/*�������*/
    {
        p=a->vertex[i].head;
        while(p!=NULL)
        {
            a->vertex[p->serialnum].in=a->vertex[p->serialnum].in+1;/*�������1*/
            p=p->next;
        }
    }
}



void creategraph(adjlist *a)/*����ͼ*/
{
    int i,n,j;
    int flag=1;
    anode *p = NULL,*q;
    while(flag)
    {
        printf("�������������������:\n");
        printf("(Ĭ��������ĵ�n�����������Ϊn)\n");
        scanf("%d %d",&a->portnum,&a->airlinenum);
        if(a->airlinenum > (a->portnum-1)*a->portnum/2||a->airlinenum==0)/*�ж�����Ļ������ͺ������Ƿ��ܹ���һ��ͼ*/
            printf("������������������:\n");
        else
            flag=0;
    }
    flag=1;
    getchar();
    for(i=1;i<=a->portnum;i++)/*�������*/
    {
        printf("�������%d����������:\n",i);
        scanf("%s",a->vertex[i].airportname);
        printf("������û�����ȫϵ��:\n");
        scanf("%s",a->vertex[i].safelevel);
        printf("����������:\n");
        scanf("%s",a->vertex[i].narration);
        a->vertex[i].head=NULL;/*ͷ����ÿ�*/
        a->vertex[i].out=0;/*���ȳ�ʼΪ0*/
    }
    for(i=1;i<=a->portnum;i++)/*������һվ����*/
    {
        getchar();
        printf("������ʣ���%s����һվ��������:\n",a->vertex[i].airportname);
        scanf("%d",&n);
        if(n>0)
        {
            p=a->vertex[i].head;
            if(p==NULL)
            {
                p=a->vertex[i].head=(anode *)malloc(sizeof(anode));/*��һ��Ҫ���ڽӵ��ͷ�������*/
                while(flag)
                {
                    printf("�������1����һվ������ź;���:\n");
                    printf("(Ĭ��������ĵ�n�����������Ϊn)\n");
                    scanf("%d %d",&p->serialnum,&p->timelength);
                    if(p->serialnum==i)
                        printf("������������������\n");
                    else
                        flag=0;
                }
                flag=1;
                printf("�����뺽����:\n");
                scanf("%s",p->routename);
                p->next=NULL;
            }
            else
            {
                for(;p->next!=NULL;p=p->next)//���ͷ��㲻Ϊ�գ���p����ƶ�����ֹ���ڽӱ����໥ָ��ʱͷ��㱻�۸�
                {;}
                n=n+1;//��Ϊ�����forֻ������if���֮��Ĳ�����Ϊ����Ӧelse���֮��Ĳ�������Ҫn����1
                flag=0;
            }
        }
        for(j=1;j<n;j++)
        {
            q=(anode *)malloc(sizeof(anode));
            q->next=NULL;
            p->next=q;
            p=q;
            if(flag==1)
                printf("�������%d����һվ������ź;���:\n",j+1);
            else
                printf("�������%d����һվ������ź;���:\n",j);
            scanf("%d %d",&p->serialnum,&p->timelength);
            printf("�����뺽����:\n");
            scanf("%s",p->routename);
        }
        for(p=a->vertex[i].head;p!=NULL;p=p->next)/*����ͼ���ڽӱ����໥ָ��*/
        {
            if(p->serialnum>i)
            {
                if(a->vertex[p->serialnum].head==NULL)
                    q=a->vertex[p->serialnum].head=(anode *)malloc(sizeof(anode));
                else
                {
                    for(q=a->vertex[p->serialnum].head;q->next!=NULL;)
                        q=q->next;
                    q->next=(anode *)malloc(sizeof(anode));
                    q=q->next;
                }
                q->next=NULL;
                q->serialnum=i;
                strcpy(q->routename,p->routename);
                q->timelength=p->timelength;
            }
        }
    }
    churudu(a);
    establish(a);
    printf("��ϲ���������!\n");
}



void readfile(adjlist *a,FILE *sfp,FILE *rfp)/*���ļ�*/
{
    int i,j;
    anode *p = NULL,*q;
    fscanf(sfp,"%d %d\n",&a->portnum,&a->airlinenum);/*�ȶ���������*/
    for(i=1;i<=a->portnum;i++)/*�������*/
    {
        fscanf(sfp,"%s %s %s %d %d\n",a->vertex[i].airportname,a->vertex[i].safelevel,a->vertex[i].narration,&a->vertex[i].in,&a->vertex[i].out);
        a->vertex[i].head=NULL;/*ͷ����ÿ�*/
    }
    for(i=1;i<=a->portnum;i++)/*������һվ����*/
    {
        if(a->vertex[i].out!=0)
        {
            a->vertex[i].head=p=(anode *)malloc(sizeof(anode));/*��һ���ȶ���ͷ�����Ϣ*/
            fscanf(rfp,"%s %d %d",p->routename,&p->serialnum,&p->timelength);
            p->next=NULL;
        }
        for(j=1;j<a->vertex[i].out;j++)
        {
            q=(anode *)malloc(sizeof(anode));
            q->next=NULL;
            p->next=q;
            p=q;
            fscanf(rfp,"%s %d %d",p->routename,&p->serialnum,&p->timelength);
        }
    }
    
}



void show(adjlist *a)/*��ʾ���л����ͺ�����Ϣ�����������ʾ*/
{
    int i;
    anode *p;
    printf("���  ��������    ������ȫϵ��   ��������\n");
    for(i=1;i<=a->portnum;i++)
        printf("%d      %s     %s     %s\n",i,a->vertex[i].airportname,a->vertex[i].safelevel,a->vertex[i].narration);
    if(a->airlinenum==0)
        printf("û�к���!\n");
    else
        printf("��������   ����ʱ��(��)   ������   �յ����\n");
    for(i=1;i<=a->portnum;i++)
    {
        for(p=a->vertex[i].head;p!=NULL;p=p->next)
            if(i<p->serialnum)
                printf("%s    %d     %d    %d\n",p->routename,p->timelength,i,p->serialnum);
    }
}



void add(int s,adjlist *a)/*���ӻ����ͺ���*/
{
    
    int n,m,i,j,y,l,flag=1;
    anode *p = NULL,*q;
    char name[20];
    system("cls");
    show(a);
    if(s==4)
    {
        printf("������������ͺ�����:\n");
        scanf("%d %d",&n,&m);
        for(i=1;i<=n;i++)
        {
            printf("�������%d���»�������:\n",i);
            scanf("%s",a->vertex[a->portnum+i].airportname);
            printf("�������%d���»�����ȫϵ��:\n",i);
            scanf("%s",a->vertex[a->portnum+i].safelevel);
            printf("�������%d���»�������:\n",i);
            scanf("%s",a->vertex[a->portnum+i].narration);
            a->vertex[a->portnum+i].out=0;/*���ȳ�ʼΪ0*/
        }
        for(i=1;i<=n;i++)/*�����»�������һվ����*/
        {
            getchar();
            printf("������%s����һվ��������:\n",a->vertex[a->portnum+i].airportname);
            scanf("%d",&y);
            if(y>0)
            {
                a->vertex[a->portnum+i].head=p=(anode *)malloc(sizeof(anode));/*��һ��Ҫ���ڽӵ��ͷ�������*/
                while(flag)
                {
                    printf("�������1����һվ������ź;���:\n");
                    scanf("%d %d",&p->serialnum,&p->timelength);
                    if(p->serialnum==a->portnum+i)
                        printf("������������������:\n");
                    else
                        flag=0;
                }
                flag=1;
                printf("�����뺽����:\n");
                scanf("%s",p->routename);
                p->next=NULL;
            }
            for(j=1;j<y;j++)
            {
                q=(anode *)malloc(sizeof(anode));
                q->next=NULL;
                p->next=q;
                p=q;
                printf("�������%d����һվ������źͺ���ʱ��(��):\n",j+1);
                scanf("%d %d",&p->serialnum,&p->timelength);
                printf("�����뺽����:\n");
                scanf("%s",p->routename);
            }
        }
        for(i=1;i<=n;i++)/*����ԭ�л������¼ӻ�������ϵ*/
            for(p=a->vertex[a->portnum+i].head;p!=NULL;p=p->next)
            {
                if(a->vertex[p->serialnum].head==NULL)
                    q=a->vertex[p->serialnum].head=(anode *)malloc(sizeof(anode));
                else
                {
                    for(q=a->vertex[p->serialnum].head;q->next!=NULL;)
                        q=q->next;
                    q->next=(anode *)malloc(sizeof(anode));
                    q=q->next;
                }
                q->next=NULL;
                q->serialnum=a->portnum+i;
                strcpy(q->routename,p->routename);
                q->timelength=p->timelength;
            }
        a->portnum=a->portnum+n;/*���ӻ�����Ļ�����*/
        a->airlinenum=a->airlinenum+m;/*���Ӻ��ߺ�ĺ�����*/
    }
    else
    {
        printf("������Ҫ�����º��ߵ�����:\n");
        scanf("%d",&y);
        a->airlinenum=a->airlinenum+y;
        for(i=1;i<=y;i++)
        {
            printf("������Ҫ�����º��ߵ������յ����:\n");
            scanf("%d %d",&m,&n);
            if(a->vertex[m].head==NULL)/*��m�����˵ĺ�����Ϣ*/
            {
                q=a->vertex[m].head=(anode *)malloc(sizeof(anode));
                q->next=NULL;
            }
            else
            {
                for(q=a->vertex[m].head;q->next!=NULL;)
                    q=q->next;
                q->next=(anode *)malloc(sizeof(anode));
                q=q->next;
                q->next=NULL;
            }
            q->serialnum=n;
            printf("�����뺽����:\n");
            scanf("%s",q->routename);
            strcpy(name,q->routename);/*�м����*/
            printf("�������%d���º��ߵĺ���ʱ��:\n",i);
            scanf("%d",&q->timelength);
            l=q->timelength;
            if(a->vertex[n].head==NULL)/*��n�����˵ĺ�����Ϣ����m�����Ӧ*/
            {
                q=a->vertex[n].head=(anode *)malloc(sizeof(anode));
                q->next=NULL;
            }
            else
            {
                for(q=a->vertex[n].head;q->next!=NULL;)
                    q=q->next;
                q->next=(anode *)malloc(sizeof(anode));
                q=q->next;
                q->next=NULL;
            }
            q->serialnum=m;
            strcpy(q->routename,name);
            q->timelength=l;
        }
    }
    churudu(a);
    establish(a);
    printf("��ϲ������ɹ���\n");
    getchar();
    printf("������������ϲ�...");
    getchar();
}



void modify(int s,adjlist *a)/*�޸Ļ�����Ϣ*/
{
    int n,i;
    FILE *sfp;
    show(a);
    printf("������Ҫ�޸ĵĻ��������:\n");
    scanf("%d",&n);
    if(s==1)
    {
        printf("���������������:\n");
        scanf("%s",a->vertex[n].airportname);
    }
    else if(s==2)
    {
        printf("����������°�ȫϵ��:\n");
        scanf("%s",a->vertex[n].safelevel);
    }
    else
    {
        printf("���������������:\n");
        scanf("%s",a->vertex[n].narration);
    }
    sfp=fopen("air.txt","wt");//�����»����ļ�
    fprintf(sfp,"%d %d\n",a->portnum,a->airlinenum);/*�������ͺ�����д��air��*/
    for(i=1;i<=a->portnum;i++)
        fprintf(sfp,"%s %s %s %d %d\n",a->vertex[i].airportname,a->vertex[i].safelevel,a->vertex[i].narration,a->vertex[i].out,a->vertex[i].in);
    fclose(sfp);//�ر��ļ�
    printf("��ϲ���޸ĳɹ���\n");
    getchar();
    printf("������������ϲ�...");
    getchar();
}



void modifyroute(int s,adjlist *a)/*�޸ĺ�����Ϣ*/
{
    int m,n,t = 0,i,j;
    char name[20];
    anode *p;
    FILE *rfp;
    show(a);
    printf("������Ҫ�޸ĵ������յ����:\n");
    scanf("%d %d",&m,&n);
    for(p=a->vertex[m].head;p!=NULL;p=p->next)
    {
        if(p->serialnum==n)
        {
            if(s==6)
            {
                printf("�����뺽��������:\n");
                scanf("%s",p->routename);
                strcpy(name,p->routename);
            }
            else
            {
                printf("�����뺽���µĺ���ʱ��:\n");
                scanf("%d",&p->timelength);
                t=p->timelength;
            }
        }
    }
    for(p=a->vertex[n].head;p!=NULL;p=p->next)/*��ΪҪ�����ļ�������һ������ͼ�����Ը���m��nҲ�͵ø�n��m������ܱ�֤�����ļ�����Ϣ��һ�µ�,��Ϊ����ͼ��ɾ����for*/
    {
        if(p->serialnum==m)
        {
            if(s==6)
                strcpy(p->routename,name);
            else
                p->timelength=t;
        }
    }
    rfp=fopen("route.txt","wt");
    for(i=1;i<=a->portnum;i++)/*������Ϣд��route��*/
    {
        p=a->vertex[i].head;
        if(a->vertex[i].out>0)
        {
            
            fprintf(rfp,"%s %d %d\n",p->routename,p->serialnum,p->timelength);
            p=p->next;
        }
        for(j=1;j<a->vertex[i].out;j++)
        {
            fprintf(rfp,"%s %d %d\n",p->routename,p->serialnum,p->timelength);
            p=p->next;
        }
    }
    fclose(rfp);//�ر��ļ�
    printf("��ϲ���޸ĳɹ���\n");
    getchar();
    printf("������������ϲ�...");
    getchar();
}



void del(int s,adjlist *a)/*ɾ�������ͺ���*/
{
    anode *p,*q;
    int n,m,i;
    show(a);
    if(s==5)
    {
        printf("������Ҫɾ���Ļ������:\n");
        scanf("%d",&n);
        for(i=1;i<=a->portnum;)
        {
            if(i==n||a->vertex[i].head==NULL)
                i++;
            else
            {
                if(a->vertex[i].head->serialnum==n)/*���ж�ͷ����Ƿ���Ҫɾ��*/
                {
                    q=a->vertex[i].head->next;
                    free(a->vertex[i].head);
                    a->airlinenum=a->airlinenum-1;
                    a->vertex[i].head=q;
                }
                else
                    for(p=a->vertex[i].head;p->next!=NULL;p=p->next)
                    {
                        q=p->next;
                        if(q->serialnum==n)
                        {
                            p->next=q->next;
                            free(q);
                            a->airlinenum=a->airlinenum-1;/*�������صĺ�������һ�����ܺ�������ȻҪ��1*/
                            break;
                        }
                    }
                i++;
            }
        }
        for(i=n;i<a->portnum;i++)/*ɾ��������Ѹû������Ԫ��������ǰ�ƶ�*/
            a->vertex[i]=a->vertex[i+1];
        a->portnum=a->portnum-1;/*�ܻ�������1*/
        for(i=1;i<=a->portnum;i++)
            for(p=a->vertex[i].head;p!=NULL;p=p->next)/*Ԫ��������ǰ�ƶ�֮��ԭ�ȴ洢�����ҲҪ����һ��*/
                if(p->serialnum>n)
                    p->serialnum--;
    }
    else
    {
        printf("������Ҫɾ�����ߵ������յ����:\n");
        scanf("%d %d",&m,&n);
        if(a->vertex[m].head->serialnum==n)/*��mΪ����ɾ������*/
        {
            q=a->vertex[m].head->next;
            free(a->vertex[m].head);
            a->airlinenum=a->airlinenum-1;/*�������غ�������һ�����ܺ�������ȻҪ��1*/
            a->vertex[m].head=q;
        }
        else
            for(p=a->vertex[m].head;p->next!=NULL;p=p->next)
            {
                q=p->next;
                if(q->serialnum==n)
                {
                    p->next=q->next;
                    free(q);
                    a->airlinenum=a->airlinenum-1;/*�������غ�������һ�����ܺ�������ȻҪ��1*/
                    break;
                }
            }
        if(a->vertex[n].head->serialnum==m)/*��mΪ����ɾ������*/
        {
            q=a->vertex[n].head->next;
            free(a->vertex[n].head);
            a->vertex[n].head=q;
        }
        else
            for(p=a->vertex[n].head;p->next!=NULL;p=p->next)
            {
                q=p->next;
                if(q->serialnum==m)
                {
                    p->next=q->next;
                    free(q);
                    break;
                }
            }
    }
    churudu(a);
    establish(a);
    printf("��ϲ��ɾ���ɹ���\n");
    getchar();
    printf("������������ϲ�...");
    getchar();
}
adjmartrix Exchange(adjlist *a)//�ڽӱ�ת��Ϊ��Ȩͼ�ڽӾ���
{
    adjmartrix b;
    anode *p;
    int i,j;
    b.portnum=a->portnum;
    for(i=1;i<=a->portnum;i++)
    {
        strcpy(b.airpotname[i],a->vertex[i].airportname);
        for(j=1;j<=a->portnum;j++)
            b.routes[i][j]=infinity;//��ʼ��Ϊ����ֵ
    }
    for(i=1;i<=a->portnum;i++)
        for(p=a->vertex[i].head;p!=NULL;p=p->next)
        {
            if(p==a->vertex[i].head)
                b.routes[i][p->serialnum]=p->timelength;
            else
                b.routes[i][p->serialnum]=p->timelength;
        }
    return b;
}



void Dijkstra(adjlist *a,adjmartrix *b,int start,int *dist,int (*path)[maxsize])//��̺����㷨
{
    int mindist,i,j,k = 0,t=1;
    for(i=1;i<=a->portnum;i++)
    {
        dist[i]=b->routes[start][i];
        if(b->routes[start][i]!=infinity)
            path[i][1]=start;
    }
    path[start][0]=1;
    for(i=2;i<=a->portnum;i++)
    {
        mindist=infinity;
        for(j=1;j<=a->portnum;j++)
        {
            if(!path[j][0]&&dist[j]<mindist)
            {
                k=j;
                mindist=dist[j];
            }
        }
        if(mindist==infinity) return;
        path[k][0]=1;
        for(j=1;j<=a->portnum;j++)
        {
            if(!path[j][0]&&b->routes[k][j]<infinity&&dist[k]+b->routes[k][j]<dist[j])
            {
                dist[j]=dist[k]+b->routes[k][j];
                t=1;
                while(path[k][t]!=0)
                {
                    path[j][t]=path[k][t];
                    t++;
                }
                path[j][t]=k;
                path[j][t+1]=0;
            }
        }
    }
}



void bestvoyage(adjlist *a)//Ѱ����̺���
{
    
    int i,start = 0,j,flag=1;
    char name[20];
    int dist[maxsize];
    int path[maxsize][maxsize];
    adjmartrix b=Exchange(a);//���ڽӱ�aת��Ϊ�ڽӾ���b
    for(i=1;i<maxsize;i++)
    {
        dist[i]=infinity;
        for(j=0;j<maxsize;j++)
            path[i][j]=0;
    }
    printf("�������������:\n");
    scanf("%s",name);
    for(i=1;i<=a->portnum;i++)
    {
        if(strcmp(b.airpotname[i],name)==0)
        {start=i;
            flag=1;
            break;
        }
        flag=0;
    }
    if(flag==0)
    {
        printf("�˻���������!");
        getchar();
        printf("������������ϲ�...");
        getchar();
        return;
    }
    Dijkstra(a,&b,start,dist,path);
    printf("%s����������������г̺���Ϊ:\n",a->vertex[start].airportname);
    for(i=1;i<=a->portnum;i++)
    {
        if(i!=start)
        {
            printf("%s",a->vertex[start].airportname);//��ʾ��̺���
            for(j=2;j<a->portnum;j++)
            {
                if(path[i][j]!=0)
                    printf("---->%s",a->vertex[path[i][j]].airportname);
                else
                    printf("---->%s",a->vertex[i].airportname);
                if(path[i][j]==0)
                    break;
            }
        }
        if(i!=start)
            printf("\n");
    }
    getchar();
    printf("������������ϲ�...");
    getchar();
}



void showall(adjlist *a)/*��ʾ���л����ͺ�����Ϣ���û�������ʾ*/
{
    int i;
    anode *p;
    printf("��������              ������ȫϵ��     ��������\n");
    for(i=1;i<=a->portnum;i++)
        printf("%-17s     %-8s     %s\n",a->vertex[i].airportname,a->vertex[i].safelevel,a->vertex[i].narration);
    printf("----------------------------------------------\n");
    printf("��������       ����ʱ��(��)          ���              �յ�\n");
    for(i=1;i<=a->portnum;i++)
    {
        for(p=a->vertex[i].head;p!=NULL;p=p->next)
            if(i<p->serialnum)
                printf("%-11s    %-10d     %-16s    %s\n",p->routename,p->timelength,a->vertex[i].airportname,a->vertex[p->serialnum].airportname);
    }
    getchar();
    printf("������������ϲ�...");
    getchar();
}
SeqStack *init_SeqStack()//�ÿ�ջ
{
    SeqStack *s;
    s=(SeqStack *)malloc(sizeof(SeqStack));
    s->top=0;
    return s;
}



void push(SeqStack *s,int x,int *visit)//��ջ
{
    s->top++;
    s->stack[s->top]=x;
    visit[x]=1;
}



void pop(SeqStack *s,int *visit)
{
    visit[s->stack[s->top]]=0;
    s->top--;
}



int Adjvex(adjmartrix *b,int v,int w)
{
    int i;
    for(i=1+w;i<=b->portnum;i++)
    {
        if(b->routes[v][i]!=infinity)
        {
            w=i;
            return i;
        }
    }
    return -1;
}



void DFS(adjmartrix *b,int start,int end,int *visit,SeqStack *s,adjlist *a)//��ȱ�������
{
    int w=0,i;
    push(s,start,visit);//start��ջ
    if(start==end)
    {   printf("%s",a->vertex[s->stack[1]].airportname);
        for(i=2;i<=s->top;i++)//���ջ�ڵ�Ԫ
            printf("--->%s",a->vertex[s->stack[i]].airportname);
        printf("\n");
        pop(s,visit);//��ջ
        return;
    }
    w=Adjvex(b,start,0);
    while(w!=-1)
    {
        
        if(!visit[w])
        {
            DFS(b,w,end,visit,s,a);
            
        }
        w=Adjvex(b,start,w);
    }
    pop(s,visit);
}



void allroute(adjlist *a)//������֮�����к���
{
    int i,end = 0,start = 0,visit[maxsize],flag=1;
    char t[20],d[20];
    SeqStack *s=init_SeqStack();
    adjmartrix b=Exchange(a);//�ڽӱ�ת���ɾ���
    for(i=1;i<=a->portnum;i++)
        visit[i]=0;
    printf("������������ƺ��յ�����(�ո����):\n");
    scanf("%s %s",t,d);
    for(i=1;i<=a->portnum;i++)
    {
        if(strcmp(t,a->vertex[i].airportname)==0)
        {
            start=i;
            flag=1;
            break;
        }
        flag=0;
    }
    if(flag==0)
    {
        printf("����㲻����!");
        getchar();
        printf("������������ϲ�...");
        getchar();
        return;
    }
    for(i=1;i<=a->portnum;i++)
    {
        if(strcmp(d,a->vertex[i].airportname)==0)
        {
            end=i;
            flag=1;
            break;
        }
        flag=0;
    }
    if(flag==0)
    {
        printf("���յ㲻����!");
        getchar();
        printf("������������ϲ�...");
        getchar();
        return;
    }
    printf("%s��%s�����к���Ϊ:\n",a->vertex[start].airportname,a->vertex[end].airportname);
    DFS(&b,start,end,visit,s,a);
    getchar();
    printf("������������ϲ�...");
    getchar();
}



void prim(adjmartrix *b,int start)//prim�㷨����ѻ��˺���
{
    struct
    {
        int adjvex;
        int lowcost;
    }closedge[maxsize];
    int i,e,s,m = 0,min;
    closedge[start].lowcost=0;
    for(i=1;i<=b->portnum;i++)
        if(i!=start)
        {
            closedge[i].adjvex=start;
            closedge[i].lowcost=b->routes[start][i];
        }
    for(e=1;e<=b->portnum-1;e++)
    {
        min=infinity;
        for(s=1;s<=b->portnum;s++)
        {
            if(closedge[s].lowcost!=0&&closedge[s].lowcost<min)
            {
                m=s;
                min=closedge[s].lowcost;
            }
            
        }
        printf("%s--->%s   ���ߺ���ʱ��Ϊ%d\n",b->airpotname[closedge[m].adjvex],b->airpotname[m],closedge[m].lowcost);
        closedge[m].lowcost=0;
        for(i=1;i<=b->portnum;i++)
            if(i!=m&&b->routes[m][i]<closedge[i].lowcost)
            {
                closedge[i].lowcost=b->routes[m][i];
                closedge[i].adjvex=m;
            }
    }
}



void bestroute(adjlist *a)
{
    int i,start = 0,flag=1;
    char t[20];
    adjmartrix b=Exchange(a);//�ڽӱ�ת���ɾ���
    printf("�������������:\n");
    scanf("%s",t);
    for(i=1;i<=a->portnum;i++)
    {
        if(strcmp(t,a->vertex[i].airportname)==0)
        {
            start=i;
            flag=1;
            break;
        }
        flag=0;
    }
    if(flag==0)
    {
        printf("�˻���������!");
        getchar();
        printf("������������ϲ�...");
        getchar();
        return;
    }
    prim(&b,start);
    getchar();
    printf("������������ϲ�...");
    getchar();
}
int key()//��������
{
    char key[20],m[20];
    FILE *s;
    s=fopen("key.txt","r");
    if(s==NULL)
    {   s=fopen("key.txt","wt");
        printf("�봴����������:\n");
        scanf("%s",key);
        fprintf(s,"%s",key);
        fclose(s);
        printf("��ϲ�������ɹ�!\n");
        getchar();
        printf("�����������...");
        getchar();
        return 1;
    }
    else
    {  fscanf(s,"%s",m);
        fclose(s);
        printf("�������������:\n");
        scanf("%s",key);
        if(strcmp(m,key)==0)
        {
            printf("������ȷ!\n");
            getchar();
            printf("�����������...");
            getchar();
            return 1;
        }
        else
        {
            printf("�������!\n");
            getchar();
            printf("�����������...");
            getchar();
            return 0;
        }
    }
    
}



void System(adjlist *a)
{
    int s,flag=1;
    system("cls");
    flag=key();
    if(flag==1)
        do
        {
            system("cls");
            printf("******************************************\n");
            printf("*            1.�޸Ļ�������              *\n");
            printf("*            2.�޸Ļ�����ȫϵ��          *\n");
            printf("*            3.�޸Ļ�������              *\n");
            printf("*            4.���ӻ���                  *\n");
            printf("*            5.ɾ������                  *\n");
            printf("*            6.�޸ĺ�������              *\n");
            printf("*            7.�޸ĺ���ʱ��              *\n");
            printf("*            8.���Ӻ���                  *\n");
            printf("*            9.ɾ������                  *\n");
            printf("*            10.���³�ʼ��(������!)      *\n");
            printf("*            0.����                      *\n");
            printf("******************************************\n");
            printf("��ѡ��:");
            scanf("%d",&s);
            system("cls");
            switch(s)
            {
                case 1:modify(s,a);break;/*�޸Ļ�������*/
                case 2:modify(s,a);break;/*�޸Ļ�����ȫϵ��*/
                case 3:modify(s,a);break;/*�޸Ļ�������*/
                case 4:add(s,a);break;/*���ӻ���*/
                case 5:del(s,a);break;/*ɾ������*/
                case 6:modifyroute(s,a);break;/*�޸ĺ�������*/
                case 7:modifyroute(s,a);break;/*�޸ĺ���ʱ��*/
                case 8:add(s,a);break;/*���Ӻ���*/
                case 9:del(s,a);break;/*ɾ������*/
                case 10:creategraph(a);break;/*���³�ʼ��(����)*/
            }
        }while(s!=0);
}



int main()
{
    int q;
    adjlist a;
    FILE *sfp,*rfp;
    sfp=fopen("air.txt","r");
    rfp=fopen("route.txt","r");
    if(sfp==NULL)
        creategraph(&a);
    else
        readfile(&a,sfp,rfp);
    do
    {
        system("cls");
        printf("\n\n\n\n\n");
        printf("**********************************************\n");
        printf("*           ��ӭʹ�ú��໻�˷���ϵͳ         *\n");
        printf("*                                            *\n");
        printf("*           1.��ʾ���л����ͺ���             *\n");
        printf("*                                            *\n");
        printf("*           2.������֮�����к���             *\n");
        printf("*                                            *\n");
        printf("*           3.��ѻ��˺��߲�ѯ               *\n");
        printf("*                                            *\n");
        printf("*           4.��Ѻ��̲�ѯ                   *\n");
        printf("*                                            *\n");
        printf("*           5.ϵͳ����                       *\n");
        printf("*                                            *\n");
        printf("*           0.�˳�ϵͳ                       *\n");
        printf("*                                            *\n");
        printf("**********************************************\n");
        printf("                ��ѡ��:");
        scanf("%d",&q);
        system("cls");
        switch(q)
        {
            case 1: showall(&a);break;
            case 2: allroute(&a);break;
            case 3: bestroute(&a);break;
            case 4: bestvoyage(&a);break;
            case 5: System(&a);break;
        }
    }while(q!=0);
}

