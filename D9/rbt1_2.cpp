#include <iostream>
using namespace std;

const static bool RED=0;
const static bool BLACK=1;

struct Node
{
	int val;
	bool color;
	Node *left,*right,*p;
	Node(const int&v,const bool &c=RED,Node*l=NULL,Node*r=NULL,Node*_p=NULL):val(v),color(c),left(l),right(r),p(_p){}
};

struct RBTree
{
	Node* root;
	Node* nil;
	RBTree()
	{
		nil=new Node(-1,BLACK,nil,nil,nil);
	}	
	//leftR
	void left_rotate(Node*x)
	{
		Node *y=x->right;
		x->right=y->left;
		if(y->left!=nil)
		{
			y->left->p=x;
		}
		y->p=x->p;
		if(x->p==nil)
		{
			root=y;
		}
		else if(x->p->left==x)
		{
			x->p->left=y;
		}
		else
		{
			x->p->right=y;
		}
		x->p=y;
		y->left=x;
	}
	//rightR
	void right_rotate(Node*x)
	{
		Node *y=x->left;
		x->left=y->right;
		if(y->right!=nil)
		{
			y->right->p=x;
		}
		y->p=x->p;
		if(x->p==nil)
		{
			root=y;
		}
		else if(x->p->left==x)
		{
			x->p->left=y;
		}
		else
		{
			x->p->right=y;
		}
		x->p=y;
		y->right=x;
	}
	//insert
	Node*insert_bst(Node*&p,Node*&r,const int&v)
	{
		if(r==nil)
		{
			r=new Node(v,RED,nil,nil,p);
			if(p==nil)
			{
				root=r;
			}
			if(v>p->val)
			{
				p->right=r;
			}
			else
			{
				p->left=r;
			}
		}
		else
		{
			if(v<r->val)
			{
				return insert_bst(r,r->left,v);
			}
			else
			{
				return insert_bst(r,r->right,v);
			}
		}
		return r;
	}
	void insert(const int &v)
	{
		Node*z=insert_bst(nil,root,v);
		while(z->p->color==RED)
		{
			if(z->p->p->left==z->p)
			{
				if(z->p->p->right->color==RED)
				{
					//A
					z->p->color=BLACK;
					z->p->p->color=RED;
					z->p->p->right->color=BLACK;
					z=z->p->p;
				}
				else
				{
					if(z->p->right==z)
					{
						//A2
						z=z->p;
						left_rotate(z);
					}
					//A3
					z->p->color=BLACK;
					z->p->p->color=RED;
					right_rotate(z->p->p);
				}
			}
			else
			{
				if(z->p->p->left->color==RED)
				{
					//B
					z->p->color=BLACK;
					z->p->p->color=RED;
					z->p->p->left->color=BLACK;
					z=z->p->p; 
				}
				else
				{
					//B2
					if(z->p->left==z)
					{
						z=z->p;
						right_rotate(z);
					}
					//B3
					z->p->color=BLACK;
					z->p->p->color=RED;
					left_rotate(z->p->p); 
				}
			}
		}
		root->color=BLACK;
	}
	//find
	Node*find_min(Node*r)
	{
		Node*p=r;
		while(r!=nil)
		{
			p=r;
			r=r->left;
		}
		return p;
	}
	Node *getNode(Node*r,const int &v)
	{
		if(r==nil)
		{
			return nil;
		} 
		if(r->val==v)
		{
			return r;
		}
		else if(v<r->val)
		{
			return getNode(r->left,v);
		}
		else
		{
			return getNode(r->right,v);
		}
	}
	Node *getNode(const int&v)
	{
		return getNode(root,v);
	}
	//delete
	void rb_delete_fixup(Node* x)
	{
		while(x!=root&&x->color==BLACK)
		{
			if(x==x->p->left)
			{
				Node*w=x->p->right;
				if(w->color==RED)
				{
					w->color=BLACK;
					w->p->color=RED;
					right_rotate(x->p);
					w=x->p->left;
				} 
				if(w->right->color==BLACK && w->right->color==BLACK)
				{
					w->color=RED;
					x=x->p;
				}
				else
				{
					if(w->right->color==BLACK)
					{
						w->left->color=BLACK;
						w->color=RED;
						right_rotate(w);
						w=x->p->right; 
					}
					w->color=x->p->color;
					x->p->color=BLACK;
					w->right->color=BLACK;
					left_rotate(x->p);
					x=root;
				}
			}else
			{
				Node *w=x->p->left;
				if(w->color==RED)
				{
					w->color=BLACK;
					x->p->color=RED;
					right_rotate(x->p);
					w=x->p->left;
				}
				if(w->right->color==BLACK&&w->left->color==RED)
				{
					w->color=RED;
					x=x->p;
				}
				else
				{
					if(w->left->color==BLACK)
					{
						w->right->color=BLACK;
						w->color=RED;
						left_rotate(w);
						w=x->p->left;
					}
					w->color=x->p->color;
					x->p->color=BLACK;
					w->left->color=BLACK;
					right_rotate(x->p);
					x=root;
				}
			}
		}
		x->color=BLACK;
	}
	void rb_transplant(Node*&u,Node*&v)
	{
		if(u->p==nil)
		{
			root=v;
		}
		else if(u==u->p->left)
		{
			u->p->right=v;
		}
		else
		{
			u->p->right=v;
		}
		v->p=u->p; 
	}
	void rb_delete(Node *z)
	{
		Node*y=z;
		bool delcol=y->color;
		Node*x=z;
		if(z->left==nil)
		{
			x=z->right;
			rb_transplant(z,z->right);
		}
		else if(z->right==nil)
		{
			x=z->left;
			rb_transplant(z,z->left);
		}
		else
		{
			y=find_min(z->right);
			delcol=y->color;
			x=y->right;
			if(y->p==z)
			{
				x->p=y;
			}
			else
			{
				rb_transplant(y,y->right);
				y->right=z->right;
				y->right->p=y;
			}
			rb_transplant(z,y);
			y->left=z->left;
			y->left->p=y;
			y->color=z->color;
		}
		if(delcol==BLACK)
		{
			rb_delete_fixup(x); 
		} 
	}
	void rb_delete(const int&v)
	{
		Node*z=getNode(root,v);
		if(z==nil)
		{
			return;
		}
		rb_delete(z);
	}
	void in_order(Node*r)
	{
		if(r==nil||r==NULL)
		{
			return;
		}
		in_order(r->left);
		cout<<r->val<<" "<<r->color<<endl;
		in_order(r->right);
	}
	void in_order()
	{
		cout<<"in: "<<endl;
		in_order(root);
	}
	void pre_order(Node*r)
	{
		if(r==nil||r==NULL)
		{
			return;
		}
		cout<<r->val<<" "<<r->color<<endl;
		pre_order(r->left);
		pre_order(r->right);
	} 
	void pre_order()
	{
		cout<<"pre: "<<endl;
		pre_order(root);
	}
}; 

int main()
{
	int n;
	cin>>n;
	int v;
	RBTree T;
	for(int i=0;i<n;i++)
	{
		cin>>v;
		T.insert(v);
	}
	T.in_order();
	T.pre_order();
	
	cout<<"-------delete 8--------"<<endl;
	T.rb_delete(8);
	T.in_order();
	T.pre_order();
	return 0;
}
