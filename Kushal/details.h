#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "header.h"

Node *addNode(int data, int version)
{
	Node *newnode = (Node *)malloc(sizeof(Node));
	newnode->data = data;
	newnode->next = NULL;
	newnode->prev = NULL;
	newnode->node_version = version;

	// mod log of the node
	newnode->mod = (Mod *)malloc(sizeof(Mod));
	newnode->mod->data = GARBAGE;
	newnode->mod->version = UNUSED;
	newnode->mod->next = NULL;
	newnode->mod->prev = NULL;

	return newnode;
}

Stack_fp *init_stack()
{
	Stack_fp *newlist = (Stack_fp *)malloc(sizeof(Stack_fp));

	if (!newlist)
	{
		printf("Error in list creation\n");
		return NULL;
	}

	newlist->live_version = 0;

	for (int i = 0; i < MAX_OP; i++)
		newlist->head[i] = NULL;

	newlist->num_el = 0;

	return newlist;
}
void print(Stack_fp *stack, int version)
{
	if (stack->live_version < version)
	{
		printf("The version is not found\n");
		return;
	}
	Node *ptr = (Node *)malloc(sizeof(Node));
	if (!ptr)
	{
		perror("MALLOC ERROR\n");
		return;
	}
	printf("The stack in version %d is/was\n", version);
	ptr = stack->head[version];
	printf("\n*******************\n");
	while (ptr)
	{
		if (ptr->node_version > version)
			break;
		if ((ptr->mod->version <= version) && (ptr->mod->version > UNUSED)) // if the mod log of a node is not empty and it happened before this version take it
		{
			printf("%2d\t", ptr->mod->data);
			ptr = ptr->mod->next;
		}
		else
		{
			printf("%2d\t", ptr->data); // if no mods done then print the original data of the node
			ptr = ptr->next;
		}
	}
	printf("\n*******************\n");
}
Node *int_update_parentLeft_list_fp(Stack_fp *list, Node *left, Node *newnode, int live_version, int version)
{

	if (left == NULL)
		return NULL;

	if (left->mod->version == UNUSED)
	{
		left->mod->data = left->data;
		left->mod->version = live_version;
		left->mod->next = newnode;
		left->mod->prev = int_update_parentLeft_list_fp(list, left->prev, left, live_version, version);

		list->head[live_version] = list->head[version];
		return left;
	}
	else
	{
		Node *newnode_parent;

		if (left->mod->version <= version)
		{
			newnode_parent = addNode(left->mod->data, live_version);
			newnode_parent->next = newnode;

			if (left->mod->prev == NULL)
			{
				list->head[live_version] = newnode_parent;
				return newnode_parent;
			}

			newnode_parent->prev = int_update_parentLeft_list_fp(list, left->mod->prev, newnode_parent, live_version, version);
		}
		else
		{
			newnode_parent = addNode(left->data, live_version);
			newnode_parent->next = newnode;

			if (left->prev == NULL)
			{
				list->head[live_version] = newnode_parent;
				return newnode_parent;
			}

			newnode_parent->prev = int_update_parentLeft_list_fp(list, left->prev, newnode_parent, live_version, version);
		}

		return newnode_parent;
	}
}

Node *int_update_parentRight_list_fp(Stack_fp *list, Node *left, Node *newnode, int live_version, int version)
{
	if (left == NULL)
		return NULL;

	if (left->node_version > version)
		return NULL;

	if (left->mod->version == UNUSED)
	{
		left->mod->data = left->data;
		left->mod->version = live_version;
		left->mod->prev = newnode;
		left->mod->next = int_update_parentRight_list_fp(list, left->next, left, live_version, version);

		return left;
	}
	else
	{
		Node *newnode_parent;

		if (left->mod->version <= version)
		{
			newnode_parent = addNode(left->mod->data, live_version);
			newnode_parent->prev = newnode;
			newnode_parent->next = int_update_parentRight_list_fp(list, left->mod->next, newnode_parent, live_version, version);
		}
		else
		{
			newnode_parent = addNode(left->data, live_version);

			newnode_parent->prev = newnode;
			newnode_parent->next = int_update_parentRight_list_fp(list, left->next, newnode_parent, live_version, version);
		}

		return newnode_parent;
	}
}

bool int_insert_list_fp(Stack_fp *list, int data, int index, int version)
{
	if (index < 0)
	{
		printf("Index cannot be negative");
		return false;
	}

	int index_count = 0;
	int live_version = list->live_version;
	Node *newnode = addNode(data, UNUSED);

	if (version > live_version)
	{
		printf("Version does not exist\n");
		return false;
	}

	Node *left = (Node *)malloc(sizeof(Node));
	Node *left_prev = (Node *)malloc(sizeof(Node));

	if (!left)
	{
		printf("Memory allocation error");
		return false;
	}

	if (!left_prev)
	{
		printf("Memory allocation error");
		return false;
	}

	for (left = list->head[version], left_prev = list->head[version]; left != NULL; index_count++)
	{
		if (left != list->head[version])
			left_prev = left;

		if (index_count == index)
			break;

		if ((left->mod->version <= version) && left->mod->version != UNUSED)
			left = left->mod->next;
		else
			left = left->next;
	}

	if (left == NULL)
		index_count--;

	if (list->head[live_version] == NULL)
	{
		list->head[live_version] = newnode;
		newnode->node_version = live_version;
		return true;
	}

	left = left_prev;

	if (left->mod->version == UNUSED)
	{
		live_version++;
		newnode->node_version = live_version;

		if (index != 0)
		{
			left->mod->next = newnode;
			left->mod->prev = left->prev;

			newnode->next = int_update_parentRight_list_fp(list, left->next, newnode, live_version, version);
			newnode->prev = int_update_parentLeft_list_fp(list, left, newnode, live_version, version);
		}
		else
		{
			newnode->next = left;
			left->mod->data = left->data;
			left->mod->next = left->next;
			left->mod->prev = newnode;
			left->mod->version = live_version;

			list->head[live_version] = newnode;
		}
	}
	else
	{
		live_version++;

		newnode->node_version = live_version;

		if (index != 0)
		{
			if (left->mod->version <= version)
			{
				newnode->next = int_update_parentRight_list_fp(list, left->mod->next, newnode, live_version, version);
				newnode->prev = int_update_parentLeft_list_fp(list, left, newnode, live_version, version);
			}
			else
			{
				newnode->next = int_update_parentRight_list_fp(list, left->next, newnode, live_version, version);
				newnode->prev = int_update_parentLeft_list_fp(list, left, newnode, live_version, version);
			}
		}
		else
		{
			Node *trailNode;
			if (left->mod->version <= version)
			{
				trailNode = addNode(left->mod->data, live_version);
				trailNode->next = int_update_parentRight_list_fp(list, left->mod->next, trailNode, live_version, version);
			}
			else
			{
				trailNode = addNode(left->data, live_version);
				trailNode->next = int_update_parentRight_list_fp(list, left->next, trailNode, live_version, version);
			}

			trailNode->prev = newnode;
			newnode->next = trailNode;

			list->head[live_version] = newnode;
		}
	}

	list->live_version = live_version;
	return true;
}

bool int_delete_list_fp(Stack_fp *list, int index, int version)
{
	if (index < 0)
	{
		printf("Index cannot be negative");
		return false;
	}

	int index_count = 0;
	int live_version = list->live_version;

	Node *left = (Node *)malloc(sizeof(Node));

	if (version > live_version)
	{
		printf("Version does not exist\n");
		return false;
	}

	if (!left)
	{
		printf("Memory allocation error");
		return false;
	}

	if (list->head[version] == NULL)
	{
		printf("List is empty. Cannot delete from empty list");
		return false;
	}

	if ((list->head[version]->next == NULL) && (list->head[version]->mod->next == NULL) || (version == 0))
	{
		live_version++;
		list->head[live_version] = NULL;

		list->live_version = live_version;
		return true;
	}

	for (left = list->head[version]; left != NULL; index_count++)
	{
		if (index_count == index)
			break;

		if ((left->mod->version <= version) && left->mod->version != UNUSED)
			left = left->mod->next;
		else
			left = left->next;
	}

	if (left == NULL)
		index_count--;

	if (index != index_count)
	{
		printf("Index not found in the list\n");
		return false;
	}
	else
	{
		if (index == 0)
		{
			if ((left->mod->version == UNUSED) || (left->mod->version > version))
			{
				if (left->next->mod->version == UNUSED)
				{
					live_version++;

					left->next->mod->data = left->next->data;
					left->next->mod->version = live_version;

					left->next->mod->next = left->next->next;
					left->next->mod->prev = left->prev;

					list->head[live_version] = left->next;
				}
				else
				{
					live_version++;
					Node *newnode;

					if (left->next->mod->version <= version)
					{
						newnode = addNode(left->next->mod->data, live_version);
						newnode->next = int_update_parentRight_list_fp(list, left->next->mod->next, newnode, live_version, version);
					}
					else
					{
						newnode = addNode(left->next->data, live_version);
						newnode->next = int_update_parentRight_list_fp(list, left->next->next, newnode, live_version, version);
					}

					list->head[live_version] = newnode;
				}
			}
			else
			{
				if (left->mod->next->mod->version == UNUSED)
				{
					live_version++;

					left->mod->next->mod->data = left->mod->next->data;
					left->mod->next->mod->version = live_version;

					left->mod->next->mod->next = left->mod->next->next;
					left->mod->next->mod->prev = left->mod->prev;

					list->head[live_version] = left->mod->next;
				}
				else
				{
					live_version++;
					Node *newnode;
					;

					if (left->mod->next->mod->version <= version)
					{
						newnode = addNode(left->mod->next->mod->data, live_version);
						newnode->next = int_update_parentRight_list_fp(list, left->mod->next->mod->next, newnode, live_version, version);
					}
					else
					{
						newnode = addNode(left->mod->next->data, live_version);
						newnode->next = int_update_parentRight_list_fp(list, left->mod->next->next, newnode, live_version, version);
					}

					list->head[live_version] = newnode;
				}
			}

			list->live_version = live_version;
			return true;
		}

		if ((left->next == NULL) && (left->mod->version == UNUSED) || (left->mod->version > version))
		{
			if (left->prev->mod->version == UNUSED)
			{
				live_version++;

				left->prev->mod->data = left->prev->data;
				left->prev->mod->version = live_version;

				left->prev->mod->next = left->next;
				left->prev->mod->prev = left->prev->prev;

				list->head[live_version] = list->head[version];
			}
			else
			{
				live_version++;
				Node *newnode;

				if (left->prev->mod->version <= version)
				{
					newnode = addNode(left->prev->mod->data, live_version);
					newnode->prev = int_update_parentLeft_list_fp(list, left->prev->mod->prev, newnode, live_version, version);

					if (left->prev->mod->prev == NULL)
						list->head[live_version] = newnode;
				}
				else
				{
					newnode = addNode(left->prev->data, live_version);
					newnode->prev = int_update_parentLeft_list_fp(list, left->prev->prev, newnode, live_version, version);

					if (left->prev->prev == NULL)
						list->head[live_version] = newnode;
				}
			}

			list->live_version = live_version;
			return true;
		}

		if ((left->mod->next == NULL) && (left->mod->version != UNUSED) && (left->mod->version <= version))
		{
			if (left->mod->prev->mod->version == UNUSED)
			{
				live_version++;

				left->mod->prev->mod->data = left->mod->prev->data;
				left->mod->prev->mod->version = live_version;

				left->mod->prev->mod->next = left->mod->next;
				left->mod->prev->mod->prev = left->mod->prev->prev;

				list->head[live_version] = list->head[version];
			}
			else
			{
				live_version++;
				Node *newnode;
				;

				if (left->mod->prev->mod->version <= version)
				{
					newnode = addNode(left->mod->prev->mod->data, live_version);
					newnode->prev = int_update_parentLeft_list_fp(list, left->mod->prev->mod->prev, newnode, live_version, version);

					if (left->mod->prev->mod->prev == NULL)
						list->head[live_version] = newnode;
				}
				else
				{
					newnode = addNode(left->mod->prev->data, live_version);
					newnode->prev = int_update_parentLeft_list_fp(list, left->mod->prev->prev, newnode, live_version, version);

					if (left->mod->prev->prev == NULL)
						list->head[live_version] = newnode;
				}
			}

			list->live_version = live_version;
			return true;
		}

		if ((left->mod->version == UNUSED) || (left->mod->version > version))
		{
			if ((left->prev->mod->version == UNUSED) && (left->next->mod->version == UNUSED))
			{
				live_version++;

				left->prev->mod->data = left->prev->data;
				left->prev->mod->version = live_version;

				left->prev->mod->next = left->next;
				left->prev->mod->prev = left->prev->prev;

				left->next->mod->data = left->next->data;
				left->next->mod->version = live_version;

				left->next->mod->next = left->next->next;
				left->next->mod->prev = left->prev;

				list->head[live_version] = list->head[version];
			}
			else if ((left->prev->mod->version == UNUSED) && (left->next->mod->version != UNUSED))
			{
				live_version++;
				Node *newnode;

				left->prev->mod->data = left->prev->data;
				left->prev->mod->version = live_version;

				left->prev->mod->next = newnode;
				left->prev->mod->prev = left->prev->prev;

				if (left->next->mod->version <= version)
				{
					newnode = addNode(left->next->mod->data, live_version);
					newnode->next = int_update_parentRight_list_fp(list, left->next->mod->next, newnode, live_version, version);
				}
				else
				{
					newnode = addNode(left->next->data, live_version);
					newnode->next = int_update_parentRight_list_fp(list, left->next->next, newnode, live_version, version);
				}

				newnode->prev = left->prev;

				list->head[live_version] = list->head[version];
			}
			else if ((left->prev->mod->version != UNUSED) && (left->next->mod->version == UNUSED))
			{
				live_version++;
				Node *newnode;

				left->next->mod->data = left->next->data;
				left->next->mod->version = live_version;

				left->next->mod->next = left->next->next;
				left->next->mod->prev = newnode;

				if (left->prev->mod->version <= version)
				{
					newnode = addNode(left->prev->mod->data, live_version);
					newnode->prev = int_update_parentLeft_list_fp(list, left->prev->mod->prev, newnode, live_version, version);

					if (left->prev->mod->prev == NULL)
						list->head[live_version] = newnode;
				}
				else
				{
					newnode = addNode(left->prev->data, live_version);
					newnode->prev = int_update_parentLeft_list_fp(list, left->prev->prev, newnode, live_version, version);

					if (left->prev->prev == NULL)
						list->head[live_version] = newnode;
				}

				newnode->next = left->next;
			}
			else
			{
				live_version++;
				Node *newnode_prev;
				Node *newnode_next;

				if (left->prev->mod->version <= version)
				{
					newnode_prev = addNode(left->prev->mod->data, live_version);
					newnode_prev->prev = int_update_parentLeft_list_fp(list, left->prev->mod->prev, newnode_prev, live_version, version);

					if (left->prev->mod->prev == NULL)
						list->head[live_version] = newnode_prev;
				}
				else
				{
					newnode_prev = addNode(left->prev->data, live_version);
					newnode_prev->prev = int_update_parentLeft_list_fp(list, left->prev->prev, newnode_prev, live_version, version);

					if (left->prev->prev == NULL)
						list->head[live_version] = newnode_prev;
				}

				if (left->next->mod->version <= version)
				{
					newnode_next = addNode(left->next->mod->data, live_version);
					newnode_next->next = int_update_parentRight_list_fp(list, left->next->mod->next, newnode_next, live_version, version);
				}
				else
				{
					newnode_next = addNode(left->next->data, live_version);
					newnode_next->next = int_update_parentRight_list_fp(list, left->next->next, newnode_next, live_version, version);
				}

				newnode_prev->next = newnode_next;
				newnode_next->prev = newnode_prev;
			}
		}
		else
		{
			if ((left->mod->prev->mod->version == UNUSED) && (left->mod->next->mod->version == UNUSED))
			{
				live_version++;

				left->mod->prev->mod->data = left->mod->prev->data;
				left->mod->prev->mod->version = live_version;

				left->mod->prev->mod->next = left->mod->next;
				left->mod->prev->mod->prev = left->mod->prev->prev;

				left->mod->next->mod->data = left->mod->next->data;
				left->mod->next->mod->version = live_version;

				left->mod->next->mod->next = left->mod->next->next;
				left->mod->next->mod->prev = left->mod->prev;

				list->head[live_version] = list->head[version];
			}
			else if ((left->mod->prev->mod->version == UNUSED) && (left->mod->next->mod->version != UNUSED))
			{
				live_version++;
				Node *newnode;

				left->mod->prev->mod->data = left->mod->prev->data;
				left->mod->prev->mod->version = live_version;

				left->mod->prev->mod->prev = left->mod->prev->prev;
				left->mod->prev->mod->next = newnode;

				if (left->mod->next->mod->version <= version)
				{
					newnode = addNode(left->mod->next->mod->data, live_version);
					newnode->next = int_update_parentRight_list_fp(list, left->mod->next->mod->next, newnode, live_version, version);
				}
				else
				{
					newnode = addNode(left->mod->next->data, live_version);
					newnode->next = int_update_parentRight_list_fp(list, left->mod->next->next, newnode, live_version, version);
				}

				newnode->prev = left->mod->prev;

				list->head[live_version] = list->head[version];
			}
			else if ((left->mod->prev->mod->version != UNUSED) && (left->mod->next->mod->version == UNUSED))
			{
				live_version++;
				Node *newnode;

				left->mod->next->mod->data = left->mod->next->data;
				left->mod->next->mod->version = live_version;

				left->mod->next->mod->next = left->mod->next->next;
				left->mod->next->mod->prev = newnode;

				if (left->mod->prev->mod->version <= version)
				{
					newnode = addNode(left->mod->prev->mod->data, live_version);
					newnode->prev = int_update_parentLeft_list_fp(list, left->mod->prev->mod->prev, newnode, live_version, version);

					if (left->mod->prev->mod->prev == NULL)
						list->head[live_version] = newnode;
				}
				else
				{
					newnode = addNode(left->mod->prev->data, live_version);
					newnode->prev = int_update_parentLeft_list_fp(list, left->mod->prev->prev, newnode, live_version, version);

					if (left->mod->prev->prev == NULL)
						list->head[live_version] = newnode;
				}

				newnode->next = left->mod->next;
			}
			else
			{
				live_version++;
				Node *newnode_prev;
				Node *newnode_next;

				if (left->mod->prev->mod->version <= version)
				{
					newnode_prev = addNode(left->mod->prev->mod->data, live_version);
					newnode_prev->prev = int_update_parentLeft_list_fp(list, left->mod->prev->mod->prev, newnode_prev, live_version, version);

					if (left->mod->prev->mod->prev == NULL)
						list->head[live_version] = newnode_prev;
				}
				else
				{
					newnode_prev = addNode(left->mod->prev->data, live_version);
					newnode_prev->prev = int_update_parentLeft_list_fp(list, left->mod->prev->prev, newnode_prev, live_version, version);

					if (left->mod->prev->prev == NULL)
						list->head[live_version] = newnode_prev;
				}

				if (left->mod->next->mod->version <= version)
				{
					newnode_next = addNode(left->mod->next->mod->data, live_version);
					newnode_next->next = int_update_parentRight_list_fp(list, left->mod->next->mod->next, newnode_next, live_version, version);
				}
				else
				{
					newnode_next = addNode(left->mod->next->data, live_version);
					newnode_next->next = int_update_parentRight_list_fp(list, left->mod->next->next, newnode_next, live_version, version);
				}

				newnode_prev->next = newnode_next;
				newnode_next->prev = newnode_prev;
			}
		}

		list->live_version = live_version;
	}
	return true;
}

bool isEmpty(Stack_fp *stack, int version)
{
	if (stack->head[version] == NULL)
		return true;
	else
		false;
}

bool push(Stack_fp *stack, int data, int version)
{
	return (int_insert_list_fp(stack, data, 0, version));
}

int pop(Stack_fp *stack, int version)
{
	return int_delete_list_fp(stack, 0, version);
}
