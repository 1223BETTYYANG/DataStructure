#include <iostream>

using namespace std;

template<class T>

struct Node {//AVL���ڵ�

    T data;

    Node* lchild;

    Node* rchild;

    int height;//ƽ������

    Node(const T& e, Node* lc, Node* rc, int h = 0)

        :data(e), lchild(lc), rchild(rc), height(h) {}

};

template<class T>

class AVLTree {

private:

    Node<T>* root;

    void insert(const T& x, Node<T>*& t);//����

    void remove(T e, Node<T>*& t);//ɾ��

    void set_empty();//���

public:

    AVLTree() {

        root = NULL;

    }

    ~AVLTree() {

        set_empty(root);

    }

    bool is_empty();

    void set_empty(Node<T>* t);

    T find_min(Node<T>* t);

    T find_max(Node<T>* t);

    int get_height(Node<T>* t);

    Node<T>* get_root();

    void insert(const T& x);

    void rotate_right(Node<T>*& t);//LL�� �ҵ���

    void rotate_left(Node<T>*& t);//RR�� ����

    void right_left(Node<T>*& t);//RL�� ���Һ�����

    void left_right(Node<T>*& t);//LR�� ���������

    void show_smaller(Node<T>* t);

    void show_bigger(Node<T>* t);

    void remove(T e);

    int tree_height(Node<T>* t);

    void get_near(Node<T>* t);

};

template<class T>

bool AVLTree<T>::is_empty() {//�ж��Ƿ�Ϊ��

    return root == NULL;

}

template<class T>

void AVLTree<T>::set_empty(Node<T>* t) {//���()�ݹ�ʵ��

    if (t != NULL) {

        set_empty(t->lchild);

        set_empty(t->rchild);

        delete t;

    }

}

template<class T>

void AVLTree<T>::set_empty() {

    this->set_empty(root);

}

template<class T>

int AVLTree<T>::get_height(Node<T>* t) {

    return t == NULL ? -1 : t->height;

}

template<class T>

Node<T>* AVLTree<T>::get_root() {

    return root;

}

template<class T>

T AVLTree<T>::find_max(Node<T>* t) {//���ֵ���

    if (t->rchild == NULL)return t->data;

    else return find_max(t->rchild);

}

template<class T>

T AVLTree<T>::find_min(Node<T>* t) {//��Сֵ���

    if (t->lchild == NULL)return t->data;

    else return find_min(t->lchild);

}

//�Ӹ��ڵ㿪ʼ��key��ڵ�ֵ�Ƚϣ����keyС�ڽڵ�ֵ�����������������key���ڽڵ�ֵ��������������ֱ���ҵ�������Ϊ��ֹͣ��ͬBST��

template<class T>

void AVLTree<T>::insert(const T& x, Node<T>*& t) {

    if (t == NULL) {

        t = new Node<T>(x, NULL, NULL);//�����ֻ��һ�����ڵ�

    }

    else if (x < t->data) {//С��ֵ�������������ݹ�ʵ�֣�

        insert(x, t->lchild);

        if (get_height(t->lchild) - get_height(t->rchild) == 2) {//�����ƽ����ת

            if (get_height(t->lchild->lchild) > get_height(t->lchild->rchild))

                rotate_right(t);//LL��

            else left_right(t);//LR��

        }

    }

    else if (x > t->data) {//���ֵ��������

        insert(x, t->rchild);

        if (get_height(t->rchild) - get_height(t->lchild) == 2) {

            if (get_height(t->rchild->lchild) > get_height(t->rchild->rchild))

                right_left(t);//RL��

            else rotate_left(t);//RR��

        }

    }

    //cout<<get_height(t->lchild)<<" "<<get_height(t->rchild)<<endl;

    t->height = max(get_height(t->lchild), get_height(t->rchild)) + 1;

}

template<class T>

void AVLTree<T>::insert(const T& x) {

    insert(x, root);

}

template<class T>

void AVLTree<T>::rotate_right(Node<T>*& t) {//LL��

    Node<T>* p = t->lchild;//t�ǲ�ƽ��Ľڵ㣬p��������

    t->lchild = p->rchild;//��ת t�����ӱ�Ϊp���Һ���

    p->rchild = t;//p���t��λ�� ��ת���

      //��ת����λ�ñ仯����Ҫ�������ߣ�����Ҫ��������

    t->height = max(get_height(t->lchild), get_height(t->rchild)) + 1;

    p->height = max(get_height(p->lchild), t->height) + 1;

    t = p;

}

template<class T>

void AVLTree<T>::rotate_left(Node<T>*& t) {//RR��(��LL�Ǿ���)

    Node<T>* p = t->rchild;

    t->rchild = p->lchild;

    p->lchild = t;

    t->height = max(get_height(t->lchild), get_height(t->rchild)) + 1;

    p->height = max(get_height(p->rchild), t->height) + 1;

    t = p;

}

template<class T>

void AVLTree<T>::left_right(Node<T>*& t) {//LR��

    rotate_left(t->lchild);//�ȶ�A�������������RR��ת 

    rotate_right(t);//�ٶ�A���LL��ת 

}

template<class T>

void AVLTree<T>::right_left(Node<T>*& t) {//RL�� ��LR����

    rotate_right(t->rchild);

    rotate_left(t);

}

/*

* 1.ɾ��Ҷ�ӽ�㡣������ֱ��ɾ����Ȼ���������ϵ���ΪAVL����


2.ɾ����Ҷ�ӽڵ㣬�ýڵ�ֻ�����ӡ��������ýڵ��ֵ�滻Ϊ���ӽڵ��ֵ��Ȼ��ɾ�����ӽڵ㡣

�����ӽڵ�ΪҶ�ӽ�㣬����ɾ�����ӽڵ�����Ϊ��1���������

��Ϊʲô���ӽڵ�ΪҶ�ӽڵ㣬��Ϊɾ���ڵ�ǰ��������AVL������AVL���Ķ���֪��ÿ���ڵ�����������ĸ߶Ȳ�ľ���ֵ<=1,

���ڸýڵ�ֻ�����ӣ�û���Һ��ӣ�������ӻ����ӽڵ㣬��ô��������ÿ���ڵ�����������ĸ߶Ȳ�ľ���ֵ<=1���������ӽڵ�ΪҶ�ӽ�㡿

3.ɾ����Ҷ�ӽڵ㣬�ýڵ�ֻ���Һ��ӡ��������ýڵ��ֵ�滻Ϊ�Һ��ӽڵ��ֵ��Ȼ��ɾ���Һ��ӽڵ㡣

���Һ��ӽڵ�ΪҶ�ӽ�㣬����ɾ���Һ��ӽڵ�����Ϊ��1�����������Ϊʲô�Һ��ӽڵ�ΪҶ�ӽڵ㣿�𰸺͵ڶ������һ����

4.ɾ����Ҷ�ӽڵ㣬�ýڵ�������ӣ������Һ��ӡ��������ýڵ��ֵ�滻Ϊ�ýڵ��ǰ���ڵ㣨���ߺ�̽ڵ㣩��Ȼ��ɾ��ǰ���ڵ㣨���ߺ�̽ڵ㣩��

��ǰ�����:����������У�һ���ڵ��ǰ����㣬���ҵ��ýڵ�����ӽڵ㣬�������ӽڵ�����һ���Һ��ӽڵ㡣������һ����Ȼ�������ߵ�ͷ��

���һ���Һ��ӽڵ㼴Ϊǰ���ڵ㡿����̽ڵ㣺����������У�һ���ڵ�ĺ�̽�㣬���ҵ��ýڵ���Һ��ӽڵ㣬�����Һ��ӽڵ�����һ�����ӽڵ㡣

������һ����Ȼ�������ߵ�ͷ�����һ�����ӽڵ㼴Ϊǰ���ڵ㡿

*/

template<class T>

void AVLTree<T>::remove(T e, Node<T>*& t) {//ɾ���ڵ�

    if (t == NULL)return;

    if (e < t->data)

        remove(e, t->lchild);

    else if (e > t->data)

        remove(e, t->rchild);

    else {//�ҵ�Ҫɾ��Ԫ����

        if (t->lchild != NULL && t->rchild != NULL) {//Ԫ���ҵ��˲���������������Ϊ��(��Ҷ�ӽڵ�)

            Node<T>* p = t->rchild;

            while (p->lchild != NULL)p = p->lchild;//��Ҫɾ���Ľڵ����������е���С�ڵ����

            t->data = p->data;

            remove(p->data, t->rchild); //�ݹ�ɾ������С�ڵ�

        }

        else {//Ԫ���ҵ��˲�������������һ��Ϊ��

            Node<T>* p = t->lchild == NULL ? t->rchild : t->lchild;//��pָ��t�ķǿ�����

            // cout<<t->data<<endl;

            delete t;

            t = p;//�ú��ӽڵ㶥��ԭ��λ��

            return;

        }

    }

    //ɾ����ڵ�֮��Ҫ���¸߶�(����Ҫ������)//�Ͳ���һ��

    if (get_height(t->lchild) - get_height(t->rchild) == 2) {

        if (get_height(t->lchild->lchild) > get_height(t->lchild->rchild))

            rotate_right(t);

        else left_right(t);

    }

    else if (get_height(t->rchild) - get_height(t->lchild) == 2) {

        if (get_height(t->rchild->lchild) > get_height(t->rchild->rchild))

            right_left(t);

        else rotate_left(t);

    }

    t->height = max(get_height(t->lchild), get_height(t->rchild)) + 1;

}

template<class T>

void AVLTree<T>::remove(T e) {

    remove(e, root);

}

template<class T>

int AVLTree<T>::tree_height(Node<T>* t) {//ƽ������(�ݹ�)

    if (t == NULL)return 0;

    int lh = 0, rh = 0;

    lh = tree_height(t->lchild) + 1;

    rh = tree_height(t->rchild) + 1;

    return max(lh, rh);

}

template<class T>

void AVLTree<T>::get_near(Node<T>* t) {//��Ϊ�߶Ȳ����Ҳ��1���������ֻ���ڸ߶Ȳ�Ϊ1��Ϊ2��ʱ���ж��Ƿ�ֻ�򵥱���չ����

    if (t == NULL)return;

    if (t->lchild == NULL && t->rchild == NULL) {//��Ҷ�ӽڵ���

        cout << t->data << " ";

        return;

    }

    int lh = 0, rh = 0;

    lh = tree_height(t->lchild);

    rh = tree_height(t->rchild);

    if (lh == 1 && rh == 2) {

        get_near(t->lchild);

    }

    else if (lh == 2 && rh == 1) {

        get_near(t->rchild);

    }

    else {

        get_near(t->lchild);

        get_near(t->rchild);

    }

}

template<class T>

void AVLTree<T>::show_smaller(Node<T>* t) {//�Ӵ�С

    if (t != NULL) {

        show_smaller(t->rchild);

        cout << t->data << " ";

        show_smaller(t->lchild);

    }

}

template<class T>

void AVLTree<T>::show_bigger(Node<T>* t) {//��С����

    if (t != NULL) {

        show_bigger(t->lchild);

        cout << t->data << " ";

        show_bigger(t->rchild);

    }

}

int main() {

    AVLTree<int> avl;


    int tmp;

    cout << endl << "-----���������-----" << endl << endl;

    for (int i = 0; i < 5; i++) {

       cin>>tmp;
        avl.insert(tmp);

    }

    cout << endl;


    /*

    int a[]={1,2,3,4,5,6,7,9,10};

    for(int i=0;i<9;i++){

        avl.insert(a[i]);

    }

    */


    cout << endl << "-----��С�������-----" << endl << endl;

    avl.show_bigger(avl.get_root());

    cout << endl;


    cout << endl << "-----�Ӵ�С���-----" << endl << endl;

    avl.show_smaller(avl.get_root());

    cout << endl;


    cout << endl << "-----���ĸ߶�-----" << endl << endl;

    cout << avl.tree_height(avl.get_root()) << endl;


    cout << endl << "-----ɾ�����һ������������-----" << endl << endl;

    avl.remove(tmp);

    avl.show_bigger(avl.get_root());

    cout << endl;


    cout << endl << "-----����������Ҷ�ڵ��ֵ-----" << endl << endl;

    avl.get_near(avl.get_root());

    cout << endl << endl;


    return 0;
}
