#include "Building_Header.h"

Building* createBuilding()
{
	Building* bld_Return = NULL;
	bld_Return = (Building *)malloc(sizeof(Building));
	if(bld_Return == NULL)
	{
		printf("[Error][createBuilding] - [MEMORY NOT ALLOCATED]\n");
		return NULL;
	}

	else
		memset(bld_Return, 0, sizeof(Building));
	
	return bld_Return;
}

Building* InitBuilding(Building* bld)
{
	bld->floor_cnt = 1;
	bld->floor = createFloor(bld->floor_cnt);

	bld->floor[0]->room_cnt = 3;
	bld->floor[0]->room = createRoom(bld->floor[0]->room_cnt);
	
	int i;
	for(i = 0; i < bld->floor[0]->room_cnt; i++)
	{
		bld->floor[0]->room[i]->space_cnt = 1;
		bld->floor[0]->room[i]->space = createSpace(bld->floor[0]->room[i]->space_cnt);
	}
	return bld;
}

Building* setBuilding(Building* bld, int floor_num, int room_num)
{
	bld->floor_cnt = floor_num;
	bld->floor = (Floor **)realloc(bld->floor, sizeof(Floor *) * bld->floor_cnt);
	int i, j;
	for(i = 0; i < bld->floor_cnt; i++)
	{
		if(bld->floor[i] == NULL)
		{
			bld->floor[i] = (Floor *)malloc(sizeof(Floor));
			bld->floor[i]->room_cnt = room_num;
			bld->floor[i]->room = createRoom(bld->floor[i]->room_cnt);		
		}
	
		else
		{
			bld->floor[i]->room_cnt = room_num;
			bld->floor[i]->room = (Room **)realloc(bld->floor[i]->room, sizeof(Room *) * bld->floor[i]->room_cnt);
		}

		for(j = 0; j < bld->floor[i]->room_cnt; j++)
		{
			if(bld->floor[i]->room[j] == NULL)
			{
				bld->floor[i]->room[j] = (Room *)malloc(sizeof(Room));
				bld->floor[i]->room[j]->room_type = rand() % 3 + 1;
				switch(bld->floor[i]->room[j]->room_type)
				{
					case STANDARD_ROOM:
						bld->floor[i]->room[j]->space_cnt = 2;
						break;

					case BUSINESS_ROOM:
						bld->floor[i]->room[j]->space_cnt = 3;
						break;

					case SWEET_ROOM:
						bld->floor[i]->room[j]->space_cnt = 4;
						break;

					default:
						printf("[Error][setBuilding] - Wrong Value!\n");
						return bld;
						break;
				}
		
				bld->floor[i]->room[j]->space = createSpace(bld->floor[i]->room[j]->space_cnt);
			}

			else
			{
				bld->floor[i]->room[j] = (Room *)realloc(bld->floor[i]->room[j], sizeof(Room));
				bld->floor[i]->room[j]->room_type = rand() % 3 + 1;

				switch(bld->floor[i]->room[j]->room_type)
				{
					case STANDARD_ROOM:
						bld->floor[i]->room[j]->space_cnt = 2;
						break;

					case BUSINESS_ROOM:
						bld->floor[i]->room[j]->space_cnt = 3;
						break;

					case SWEET_ROOM:
						bld->floor[i]->room[j]->space_cnt = 4;
						break;

					default:
						printf("[Error][setBuilding] - Wrong Value!\n");
						return bld;
						break;
				}
				bld->floor[i]->room[j]->flag = 0;
				bld->floor[i]->room[j]->space = createSpace(bld->floor[i]->room[j]->space_cnt);
			}
		}
	}	
	return bld;
}
/*************/
/****FLOOR****/
/*************/
Floor** createFloor(int cnt)
{
	Floor** fl_Return = NULL;
	fl_Return = (Floor **)malloc(sizeof(Floor *) * cnt);

	int i;
	for(i = 0; i < cnt; i++)
	{
		fl_Return[i] = (Floor *)malloc(sizeof(Floor));
		memset(fl_Return[i], 0, sizeof(Floor));
	}
	if(fl_Return == NULL)
	{
		printf("[Error][createFloor] - [MEMORY NOT ALLOCATED\n");
		return NULL;
	}

	return fl_Return;
}

Floor** addFloor(Building* bld, int cnt)
{
	int i;

	bld->floor_cnt += cnt;
	bld->floor = (Floor **)realloc(bld->floor, sizeof(Floor *) * bld->floor_cnt);
	
	for(i = bld->floor_cnt - cnt; i < bld->floor_cnt; i++)
	{
		bld->floor[i] = (Floor *)malloc(sizeof(Floor));
		memset(bld->floor[i], 0, sizeof(Floor));
		bld->floor[i]->room_cnt = 1;
		bld->floor[i]->room = createRoom(bld->floor[i]->room_cnt);
	}
	
	return bld->floor;
}

Floor** delFloor(Building* bld, int cnt)
{
	int i, j ,k;
	for(i = bld->floor_cnt - 1; i > bld->floor_cnt-1-cnt; i--)
	{
		for(j = 0; j < bld->floor[i]->room_cnt; j++)
		{
			for(k = 0; k < bld->floor[i]->room[j]->space_cnt; k++)
			{
				if(bld->floor[i]->room[j]->space[k] != NULL)
					free(bld->floor[i]->room[j]->space[k]->host_name);
			}
			free(bld->floor[i]->room[j]->space);
			free(bld->floor[i]->room[j]);
		}
		free(bld->floor[i]);
	}

	bld->floor_cnt -= cnt;
	bld->floor = (Floor **)realloc(bld->floor, sizeof(Floor *) * bld->floor_cnt);

	return bld->floor;
}


/************/
/****ROOM****/
/************/
Room** createRoom(int cnt)
{
	Room** rm_Return;
	rm_Return = (Room **)malloc(sizeof(Room *) * cnt);
	
	int i;
	for(i = 0; i < cnt; i++)
	{
		rm_Return[i] = (Room *)malloc(sizeof(Room));
		memset(rm_Return[i], 0, sizeof(Room));
	}

	if(rm_Return == NULL)
	{
		printf("[Error][createRoom] - [MEMORY NOT ALLOCATED]\n");
		return NULL;
	}

	return rm_Return;
}

Room** addRoom(Floor* fl, int cnt)
{
	fl->room_cnt += cnt;
	fl->room = (Room **)realloc(fl->room, sizeof(Room *) * fl->room_cnt);
	int i;
	for(i = fl->room_cnt - cnt; i < fl->room_cnt; i++)
	{
		fl->room[i] = (Room *)malloc(sizeof(Room));
		memset(fl->room[i], 0, sizeof(Room));
		fl->room[i]->space_cnt = 1;
		fl->room[i]->space = createSpace(fl->room[i]->space_cnt);
	}

	return fl->room;
}


Room** delRoom(Floor* fl, int cnt)
{
	int i, j;

	for(i = fl->room_cnt - 1; i > fl->room_cnt - 1 - cnt; i--)
	{
		for(j = 0; j < fl->room[i]->space_cnt; j++)
		{
			free(fl->room[i]->space[j]->host_name);
		}
		free(fl->room[i]->space);
		free(fl->room[i]);
	}

	fl->room_cnt -= cnt;
	fl->room = (Room **)realloc(fl->room, sizeof(Room *) * fl->room_cnt);

	return fl->room;
}

/*************/
/****SPACE****/
/*************/
Space** createSpace(int cnt)
{
	Space** sp_Return;
	sp_Return = (Space **)malloc(sizeof(Space *) * cnt);

	int i;
	for(i = 0; i < cnt; i++)
	{
		sp_Return[i] = (Space *)malloc(sizeof(Space));
		sp_Return[i]->host_name = NULL;
	}

	if(sp_Return == NULL)
	{
		printf("[Error][createSpace] - [MEMORY NOT ALLOCATED]\n");
		return NULL;
	}

	return sp_Return;
}

Space** addSpace(Room* rm)
{
	rm->space = (Space **)realloc(rm->space,sizeof(Space *) * rm->space_cnt);
	int i;
	for(i = 0; i < rm->space_cnt; i++)
	{
		if(rm->space[i] == NULL)
		{
			rm->space[i] = (Space *)malloc(sizeof(Space));
			rm->space[i]->host_name = NULL;
		}	
	}
	return rm->space;
}

Space** delSpace(Room* rm, int cnt)
{
	int i;
	for(i = rm->space_cnt - 1; i > rm->space_cnt - 1 - cnt; i--)
	{
		free(rm->space[i]->host_name);
		free(rm->space[i]);
	}

	rm->space_cnt -= cnt;
	rm->space = (Space **)realloc(rm->space, sizeof(Space *) * rm->space_cnt);

	return rm->space;
}

void change_name(Room* rm, int from, int to)
{
	char* temp = (char *)malloc(sizeof(char));
	strcpy(temp, rm->space[to]->host_name);
	strcpy(rm->space[to]->host_name, rm->space[from]->host_name);
	strcpy(rm->space[from]->host_name, temp);
}

int* assign_a_room(Building* bld, int* room_info, int room_type)
{
	int floor_num, room_num;
	int i, j;
	printf("room_type = %d\n", room_type);
	for(i = 0; i < bld->floor_cnt; i++)
	{
		for(j = 0; j < bld->floor[i]->room_cnt; j++)
		{
			if(bld->floor[i]->room[j]->room_type == room_type && bld->floor[i]->room[j]->flag == 0)
			{
				room_info[0] = i;
				room_info[1] = j;
				return room_info;			
			}
		}
	}

	return room_info;
}

int check_room(Building* bld, int room_type)
{
	int i, j;
	int floor_num, room_num;

	if(room_type == 4)
	{
		for(i = 0; i < bld->floor_cnt; i++)
		{
			for(j = 0; j < bld->floor[i]->room_cnt; j++)
			{
				if(bld->floor[i]->room[j]->flag == 0)
				{
					return 0;
				}
			}
		}
	}

	else
	{
		for(i = 0; i < bld->floor_cnt; i++)
		{
			for(j = 0; j < bld->floor[i]->room_cnt; j++)
			{
				if(bld->floor[i]->room[j]->flag == 0 && bld->floor[i]->room[j]->room_type == room_type)
				{
					return 0;
				}
			}
		}
	}
	
	return -1;
}

void save_data(Building* bld, int* room_info, int price)
{
	
	bld->floor[room_info[0]]->room[room_info[1]]->price = price;
	bld->floor[room_info[0]]->room[room_info[1]]->electric_bill = getElePrice();
	bld->floor[room_info[0]]->room[room_info[1]]->water_bill = getWaterPrice();

	int i;
	for(i = 0; i < bld->floor[room_info[0]]->room[room_info[1]]->space_cnt; i++)
	{
		if(bld->floor[room_info[0]]->room[room_info[1]]->space[i]->host_name == NULL)
		{
			bld->floor[room_info[0]]->room[room_info[1]]->space[i]->host_name = (char *)malloc(sizeof(char));
			strcpy(bld->floor[room_info[0]]->room[room_info[1]]->space[i]->host_name, "NONE");		
		}	
	}

	print_space(bld->floor[room_info[0]]->room[room_info[1]], room_info[0], room_info[1]);
	for(i = 0; i < bld->floor[room_info[0]]->room[room_info[1]]->space_cnt; i++)
	{
		printf("Input a person name %d to stay at %d-%d room\n", i + 1, room_info[0] + 1, room_info[1] + 1);
		printf("=> ");
		scanf("%s", bld->floor[room_info[0]]->room[room_info[1]]->space[i]->host_name);
	}
	
	bld->floor[room_info[0]]->room[room_info[1]]->flag = 1;
	print_space(bld->floor[room_info[0]]->room[room_info[1]], room_info[0], room_info[1]);
}

int calculate(Building* bld)
{
	int i, j, k, result = 0;
	for(i = 0; i < bld->floor_cnt; i++)
	{
		for(j = 0; j < bld->floor[i]->room_cnt; j++)
		{
			if(bld->floor[i]->room[j]->flag == 1)
			{
				result += bld->floor[i]->room[j]->price;
				result -= bld->floor[i]->room[j]->electric_bill;
				result -= bld->floor[i]->room[j]->water_bill;
				
				bld->floor[i]->room[j]->flag = 0;
				bld->floor[i]->room[j]->electric_bill = 0;
				bld->floor[i]->room[j]->water_bill = 0;
				bld->floor[i]->room[j]->price = 0;

				for(k = 0; k < bld->floor[i]->room[j]->space_cnt; k++)
				{
						free(bld->floor[i]->room[j]->space[k]->host_name);
						bld->floor[i]->room[j]->space[k]->host_name = NULL;
				}			
			}
		}
	}

	return result;
}

