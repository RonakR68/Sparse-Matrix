#include <iostream>
#include <algorithm> //sort
using namespace std;

//define row-col-val
template <class T> class rcv{
    private:
    int row;
    int col;
    T val;
    rcv* next;

    public:
    rcv() : row(0), col(0), val(T()), next(nullptr){}

    rcv(int r, int c, T v) : row(r), col(c), val(v), next(nullptr){}

    int getRow(){
        return row;
    }

    int getCol(){
        return col;
    }

    void setRow(int r){
        row = r;
    }

    void setCol(int c){
        col = c;
    }

    T getVal(){
        return val;
    }

    void setVal(T v){
        val = v;
    }

    rcv* getNext(){
        return next;
    }

    void setNext(rcv* node){
        next = node;
    }
};

//define vector
template <class T> class vect{
    private:
    int sz, capacity;

    public:
    T *arr = nullptr;

    void resize(){
        int oldCap = capacity, newCap;
        newCap = oldCap == 0 ? 1 : 2*oldCap;
        T *temp = new T[newCap];
        for(int i=0; i<capacity; i++){
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
        capacity = newCap;
    }

    vect(){
        sz = 0;
        capacity = 0;
    }

    int size(){
        return sz;
    }

    void push_back(T val){
        if(sz == capacity){
            resize();
        }
        arr[sz] = val;
        sz++;
    }

    T& operator[](int ind){
        return arr[ind];
    }
};

//define linkedlist
template <class T> class LinkedList{
private:
    rcv<T>* head;
    rcv<T>* tail;

public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    void push_back(int row, int col, T val){
        rcv<T>* newNode = new rcv<T>(row, col, val);
        if (!head){
            head = newNode;
            tail = newNode;
        }
        else{
            tail->setNext(newNode);
            newNode->setNext(nullptr);
            tail = newNode;
        }
    }

    rcv<T>* begin(){
        return head;
    }

    rcv<T>* end(){
        return tail;
    }
};

//print array output
template <class T>
void showOutput(vect <rcv<T>> &ans, int n, int m){
    int k=0;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            int r = -1,c = -1;
            T v = T();
            if(k<ans.size()){
                r = ans[k].getRow();
                c = ans[k].getCol();
                v = ans[k].getVal();
            }
            if(i == r && j == c){
                cout<<v<<" ";
                k++;
            }
            else{
                cout<<T()<<" ";
            }
        }
        cout<<endl;
    }
}

//print linkedlist output
template <class T>
void showOutputList(LinkedList<T> &ans, int n, int m){
    rcv<T>* current = ans.begin();
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(current && current->getRow() == i && current->getCol() == j){
                cout << current->getVal() << " ";
                current = current->getNext();
            }
            else{
                cout<<T()<<" ";
            }
        }
        cout<<endl;
    }
}

//perform addition for arrays
template <class T>
void addArr(vect <rcv<T>> &v1, vect <rcv<T>> &v2, int n, int m){
    vect <rcv<T>> ans;
    int i=0, j=0;
    while(i < v1.size() && j < v2.size()){
        int r1 = v1[i].getRow();
        int c1 = v1[i].getCol();
        int r2 = v2[j].getRow();
        int c2 = v2[j].getCol();
        if(r1 < r2){
            ans.push_back(rcv<T>(r1,c1,v1[i].getVal()));
            i++;
        }
        else if((r1 == r2) && (c1 < c2)){
            ans.push_back(rcv<T>(r1,c1,v1[i].getVal()));
            i++;
        }
        else if((r1 == r2) && (c1 == c2)){
            ans.push_back(rcv<T>(r1,c1,v1[i].getVal()+v2[j].getVal()));
            i++;
            j++;
        }
        else if((r1 == r2) && (c1 > c2)){
            ans.push_back(rcv<T>(r2,c2,v2[j].getVal()));
            j++;
        }
        else{
            ans.push_back(rcv<T>(r2,c2,v2[j].getVal()));
            j++;
        }
    }
    while(i < v1.size()){
        int r1 = v1[i].getRow();
        int c1 = v1[i].getCol();
        ans.push_back(rcv<T>(r1,c1,v1[i].getVal()));
        i++;
    }
    while(j < v2.size()){
        int r2 = v2[j].getRow();
        int c2 = v2[j].getCol();
        ans.push_back(rcv<T>(r2,c2,v2[j].getVal()));
        j++;
    }
    showOutput(ans, n, m);
}

//perform addition for linkedlist
template <class T>
void addList(LinkedList<T>& l1, LinkedList<T>& l2, int n, int m){
    LinkedList<T> ans;
    rcv<T>* currentL1 = l1.begin();
    rcv<T>* currentL2 = l2.begin();

    while(currentL1 && currentL2){
        int r1 = currentL1->getRow();
        int c1 = currentL1->getCol();
        T val1 = currentL1->getVal();
        int r2 = currentL2->getRow();
        int c2 = currentL2->getCol();
        T val2 = currentL2->getVal();

        if (r1 < r2 || (r1 == r2 && c1 < c2)){
            ans.push_back(r1, c1, val1);
            currentL1 = currentL1->getNext();
        } 
        else if(r1 == r2 && c1 == c2){
            ans.push_back(r1, c1, val1 + val2);
            currentL1 = currentL1->getNext();
            currentL2 = currentL2->getNext();
        } 
        else{
            ans.push_back(r2, c2, val2);
            currentL2 = currentL2->getNext();
        }
    }
    while(currentL1){
        int r1 = currentL1->getRow();
        int c1 = currentL1->getCol();
        T val1 = currentL1->getVal();
        ans.push_back(r1, c1, val1);
        currentL1 = currentL1->getNext();
    }
    while(currentL2){
        int r2 = currentL2->getRow();
        int c2 = currentL2->getCol();
        T val2 = currentL2->getVal();
        ans.push_back(r2, c2, val2);
        currentL2 = currentL2->getNext();
    }
    showOutputList(ans, n, m);
}

//comparator
template <class T>
bool comp(rcv<T> &a, rcv<T> &b){
    if(a.getRow() == b.getRow()){
        return a.getCol() < b.getCol();
    }
    return a.getRow() < b.getRow();
}

//clear linkedlist
template <class T>
void clearList(LinkedList<T>& list){
    rcv<T>* current = list.begin();
    while(current){
        rcv<T>* temp = current;
        current = current->getNext();
        delete temp;
    }
    list = LinkedList<T>();
}

//sort linkedlist
template <class T>
void sortLinkedList(LinkedList<T> &list){
    vect<rcv<T>> temp;
    rcv<T>* current = list.begin();
    while(current){
        temp.push_back(*current);
        current = current->getNext();
    }
    sort(temp.arr, temp.arr+temp.size(), comp<T>);
    clearList(list);
    for(int i = 0; i < temp.size(); i++){
        list.push_back(temp[i].getRow(), temp[i].getCol(), temp[i].getVal());
    }
}

//peform transpose for array
template <class T>
void transposeArr(vect <rcv<T>> &v1, int n, int m){
    int s = v1.size();
    for(int i=0; i<s; i++){
        int r = v1[i].getRow();
        int c = v1[i].getCol();
        //cout<<"changing ("<<r<<","<<c<<") to ("<<c<<","<<r<<")"<<endl;
        v1[i].setRow(c);
        v1[i].setCol(r);      
    }
    sort(v1.arr, v1.arr+v1.size(), comp<T>);
    // cout<<"transposed nonzero matrix:"<<endl;
    // for(int i=0; i<s; i++){
    //     cout<<"("<<v1[i].getRow()<<","<<v1[i].getCol()<<","<<v1[i].getVal()<<") "<<endl;      
    // }
    showOutput(v1, m, n);
}

//perform transpose for linkedlist
template <class T>
void transposeList(LinkedList<T>& l1, int n, int m){
    LinkedList<T> ans;
    rcv<T>* currentL1 = l1.begin();

    while(currentL1){
        int r1 = currentL1->getRow();
        int c1 = currentL1->getCol();
        T val1 = currentL1->getVal();
        ans.push_back(c1, r1, val1);
        currentL1 = currentL1->getNext();
    }
    sortLinkedList(ans);
    showOutputList(ans, m, n);
}

//perform array multiplication
template <class T>
void multiplyArr(vect <rcv<T>> &v1, vect <rcv<T>> &v2, int n, int m){
    vect<rcv<T>> ans;
    for(int i = 0; i < v1.size(); i++){
        int r1 = v1[i].getRow();
        int c1 = v1[i].getCol();
        T val1 = v1[i].getVal();
        //cout<<"v1: ("<<r1<<", "<<c1<<", "<<val1<<")"<<endl;
        for(int j = 0; j < v2.size(); j++){
            int r2 = v2[j].getRow();
            int c2 = v2[j].getCol();
            T val2 = v2[j].getVal();
            //cout<<"v2: ("<<r2<<", "<<c2<<", "<<val2<<")"<<endl;
            if(c1 == r2){
                T newVal = val1*val2;
                int newRow = r1;
                int newCol = c2;
                ans.push_back(rcv<T>(newRow, newCol, newVal));
                //cout<<"ans: ("<<ans[ans.size()-1].getRow()<<", "<<ans[ans.size()-1].getCol()<<", "<<ans[ans.size()-1].getVal()<<")"<<endl;
            }
        }
    }
    sort(ans.arr, ans.arr+ans.size(), comp<T>);
    // cout<<"sorted ans matrix:"<<endl;
    // for(int i=0; i<ans.size(); i++){
    //     cout<<"("<<ans[i].getRow()<<","<<ans[i].getCol()<<","<<ans[i].getVal()<<") "<<endl;      
    // }
    vect<rcv<T>> res;
    int k=0;
    while(k < ans.size()){
        int r = ans[k].getRow();
        int c = ans[k].getCol();
        T v = ans[k].getVal();
        k++;
        while(k < ans.size() && r == ans[k].getRow() && c == ans[k].getCol()){
            v += ans[k].getVal();
            k++;
        }
        res.push_back(rcv<T>(r,c,v));
    }
    showOutput(res, n, m);
}

//perform linkedlist multiplication
template <class T>
void multiplyList(LinkedList<T>& l1, LinkedList<T>& l2, int n, int m) {
    LinkedList<T> ans;
    rcv<T>* currentL1 = l1.begin();
    while(currentL1){
        int r1 = currentL1->getRow();
        int c1 = currentL1->getCol();
        T val1 = currentL1->getVal();
        rcv<T>* currentL2 = l2.begin();
        while(currentL2){
            int r2 = currentL2->getRow();
            int c2 = currentL2->getCol();
            T val2 = currentL2->getVal();
            if(c1 == r2){
                T newVal = val1 * val2;
                int newRow = r1;
                int newCol = c2;
                ans.push_back(newRow, newCol, newVal);
            }
            currentL2 = currentL2->getNext();
        }
        currentL1 = currentL1->getNext();
    }
    sortLinkedList(ans);
    LinkedList<T> res;
    rcv<T>* curr = ans.begin();
    while(curr){
        int r1 = curr->getRow();
        int c1 = curr->getCol();
        T v1 = 0;
        while(curr && curr->getRow() == r1 && curr->getCol() == c1){
            v1 += curr->getVal();
            curr = curr->getNext();
        }
        res.push_back(r1, c1, v1);
    }
    showOutputList(res, n, m);
}

int main(){

    int choice_ds, choice_op;
    int q;
    cin >> q;

    while(q--){
         cin >> choice_ds;
        cin >> choice_op;
        int ip_val;
        if(choice_ds == 1){
            //array
            if(choice_op == 2){
                //transpose
                int n1, m1; //rows, cols of matrix
                vect <rcv<int>> v1;
                cin>>n1>>m1;
                //get input for matrix
                for(int i=0; i<n1; i++){
                    for(int j=0; j<m1; j++){
                        cin >> ip_val;
                        if(ip_val != 0){
                            v1.push_back(rcv<int>(i,j,ip_val));
                        }
                    }
                }
                transposeArr(v1,n1,m1);
            }

            else if(choice_op == 1 || choice_op == 3){
                //addition or multiplication
                int n1, m1, n2, m2;
                vect <rcv<int>> v1;
                vect <rcv<int>> v2;
                cin>>n1>>m1;

                //get input for matrix 1
                for(int i=0; i<n1; i++){
                    for(int j=0; j<m1; j++){
                        cin >> ip_val;
                        if(ip_val != 0){
                            v1.push_back(rcv<int>(i,j,ip_val));
                        }
                    }
                }

                cin>>n2>>m2;
                //get input for matrix 2
                for(int i=0; i<n2; i++){
                    for(int j=0; j<m2; j++){
                        cin >> ip_val;
                        if(ip_val != 0){
                            v2.push_back(rcv<int>(i,j,ip_val));
                        }
                    }
                }

                if(choice_op == 1)
                    addArr(v1, v2, n1, m1);
                if(choice_op == 3)
                    multiplyArr(v1, v2, n1, m2);
            }

        }
        else if(choice_ds == 2){
            // Linked List
            if(choice_op == 2){
                // Transpose
                int n1, m1; // Rows, cols of matrix
                LinkedList<int> l1; //change datatype here if needed
                cin >> n1 >> m1;

                // Get input for matrix
                for (int i = 0; i < n1; i++) {
                    for (int j = 0; j < m1; j++) {
                        cin >> ip_val;
                        if (ip_val != 0) {
                            l1.push_back(i, j, ip_val);
                        }
                    }
                }
                transposeList(l1, n1, m1);
            }
            else if(choice_op == 1 || choice_op == 3){
                // Addition or multiplication
                int n1, m1, n2, m2;
                LinkedList<int> l1; //change datatype here if needed
                LinkedList<int> l2; //change datatype here if needed
                cin >> n1 >> m1;

                // Get input for matrix 1
                for (int i = 0; i < n1; i++) {
                    for (int j = 0; j < m1; j++) {
                        cin >> ip_val;
                        if (ip_val != 0) {
                            l1.push_back(i, j, ip_val);
                        }
                    }
                }

                cin >> n2 >> m2;

                // Get input for matrix 2
                for (int i = 0; i < n2; i++) {
                    for (int j = 0; j < m2; j++) {
                        cin >> ip_val;
                        if (ip_val != 0) {
                            l2.push_back(i, j, ip_val);
                        }
                    }
                }

                if (choice_op == 1)
                    addList(l1, l2, n1, m1);
                if (choice_op == 3)
                    multiplyList(l1, l2, n1, m2);

            }
        }
    }

    return 0;
}
