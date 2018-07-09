#include <stdio.h>
#include <vector>
#include <string>

class SParseContext
{
public:
	const char* line;
	int p;
};

class STreeItem
{
public:
	std::string name;
	std::vector<int>children;
};

class SParseTree
{
public:
	std::vector<STreeItem>items={{"",{}}};
};

int TreeItem(SParseTree& tree, const std::string& name, const std::vector<int>&children)
{
	printf("Create tree item %lu %s (", tree.items.size(), name.c_str());
	for(int i=0;i<children.size();i++)
		printf(" %i", children[i]);
	printf(")\n");
	tree.items.push_back({name,children});
	return tree.items.size()-1;
}

inline int Expect(SParseContext& c,const char* expected, SParseTree& tree)
{
	printf("Check %s in %s\n", expected,c.line+c.p);
	if(c.line[c.p]==expected[0])
	{
		c.p++;
		return TreeItem(tree,expected,{});
	}
	return 0;
}

template <typename T>int Optional(SParseContext& c0, SParseTree& tree, T f)
{
	int t=f(c0,tree);
	if(t)
		return TreeItem(tree,"Optional",{t});
	return TreeItem(tree,"Optional",{});
}

template <typename T>int ZeroOrMore(SParseContext& c0, SParseTree& tree, T f)
{
	std::vector<int>items;
	while(true)
	{
		int t=f(c0,tree);
		if(t)
			items.push_back(t);
		else
			break;
	}
	return TreeItem(tree,"ZeroOrMore",items);
}

template <typename T>int OneOrMore(SParseContext& c0, SParseTree& tree, T f)
{
	std::vector<int>items;
	int t=f(c0,tree);
	if(f)
	{
		items.push_back(t);
		while(true)
		{
			int t=f(c0,tree);
			if(t)
				items.push_back(t);
			else
				break;
		}
	}
	else
		return 0;
	return TreeItem(tree,"OneOrMore",items);
}

int String(SParseContext& c0, SParseTree& tree)
{
	return 0;
}

int Identifier(SParseContext& c0, SParseTree& tree)
{
	return 0;
}

int IntegerConstant(SParseContext& c0, SParseTree& tree)
{
	return 0;
}

int FloatingConstant(SParseContext& c0, SParseTree& tree)
{
	return 0;
}

int EnumerationConstant(SParseContext& c0, SParseTree& tree)
{
	return 0;
}

int CharacterConstant(SParseContext& c0, SParseTree& tree)
{
	return 0;
}

int Float(SParseContext& c, SParseTree& tree)
{
	printf("Check float in %s\n",c.line+c.p);
	if(isdigit(c.line[c.p]))
	{
		std::string s(1,c.line[c.p]);
		c.p++;
		return TreeItem(tree,s,{});
	}
	return 0;
}

int Var(SParseContext& c, SParseTree& tree)
{
	printf("Check var in %s\n",c.line+c.p);
	if(isalpha(c.line[c.p]))
	{
		std::string s(1,c.line[c.p]);
		c.p++;
		return TreeItem(tree,s,{});
	}
	return 0;
}

#include "1.h"

void List(const SParseTree& tree, const STreeItem& item, int level=0)
{
	for(int i=0;i<level;i++)
		printf(" . .");
	printf("'%s'\n", item.name.c_str());
	for(const auto &child : item.children)
		List(tree, tree.items[child], level+1);
}

int main(int argc, char** argv)
{
	SParseContext c;
	c.p=0;
	c.line="x+2*(y+5)";
	SParseTree t;
	int root=Expression(c,t);
	printf("\nTree\n");
	List(t,t.items[root],0);
	return 0;
}

