#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "j1Collision.h"
#include "j1Player.h"
#include "j1Physics.h"
#include <math.h>

j1Map::j1Map() : j1Module(), map_loaded(false)
{
	name.create("map");
}

// Destructor
j1Map::~j1Map()
{}

// Called before render is available
bool j1Map::Awake(pugi::xml_node& config)
{
	LOG("Loading Map Parser");
	bool ret = true;

	folder.create(config.child("folder").child_value());

	pugi::xml_node i;
	for (i = config.child("map"); i && ret; i = i.next_sibling("map"))
	{
		p2SString set;

		if (ret == true)
		{
			set = i.attribute("directory").as_string("error");
		}

		maps.add(set);
	}
	index_map = config.child("initial_map").attribute("value").as_uint(0);
	current_map = maps[index_map];
	return ret;
}

void j1Map::Draw()
{
	if(map_loaded == false)
		return;

	SDL_Rect rect = {0,0,0,0};
	p2List_item<map_layer*>* item;
	item = data.layers.start;

		while (item != NULL)
		{	
			if (item->data->logic_layer == false)
			{ 
			for (int _y = 0; _y < item->data->height; ++_y)
			{
				for (int _x = 0; _x < item->data->width; ++_x)
				{
					iPoint point = MapToWorld(_x, _y);

					App->render->Blit(
						data.tilesets.start->data->texture,
						point.x, point.y,
						&data.tilesets.start->data->GetTileRect(item->data->data[item->data->Get(_x, _y)]));
				}
			}

		}			
		item = item->next;
	}
}


iPoint j1Map::MapToWorld(int x, int y) const
{
	iPoint ret;

	ret.x = x * data.tile_width;
	ret.y = y * data.tile_height;

	return ret;
}

SDL_Rect TileSet::GetTileRect(int id) const
{
	int relative_id = id - firstgid;
	SDL_Rect rect;
	rect.w = tile_width;
	rect.h = tile_height;
	rect.x = margin + ((rect.w + spacing) * (relative_id % num_tiles_width));
	rect.y = margin + ((rect.h + spacing) * (relative_id / num_tiles_width));
	return rect;
}

// Called before quitting
bool j1Map::CleanUp()
{
	LOG("Unloading map");

	// Remove all tilesets
	p2List_item<TileSet*>* item;
	item = data.tilesets.start;

	while(item != NULL)
	{
		RELEASE(item->data);
		item = item->next;
	}
	data.tilesets.clear();

	// TODO 2: clean up all layer data
	// Remove all layers
	
	p2List_item<map_layer*>* item_1;
	item_1 = data.layers.start;

	while (item_1 != NULL)
	{
		RELEASE(item_1->data)
		item_1 = item_1->next;
	}
	data.layers.clear();

	for (int i = 0; i < 500; ++i)
	{
		if (data.colliders[i] != nullptr)
		{
			data.colliders[i]->to_delete = true;
			data.colliders[i] = nullptr;
		}
	}

	// Clean up the pugui tree
	map_file.reset();

	return true;
}

// Load new map
bool j1Map::Load(const char* file_name)
{
	bool ret = true;
	p2SString tmp("%s%s", folder.GetString(), file_name);

	pugi::xml_parse_result result = map_file.load_file(tmp.GetString());

	if(result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		ret = false;
	}

	// Load general info ----------------------------------------------
	if(ret == true)
	{
		ret = LoadMap();
	}

	// Load all tilesets info ----------------------------------------------
	pugi::xml_node tileset;
	for(tileset = map_file.child("map").child("tileset"); tileset && ret; tileset = tileset.next_sibling("tileset"))
	{
		TileSet* set = new TileSet();

		if(ret == true)
		{
			ret = LoadTilesetDetails(tileset, set);
		}

		if(ret == true)
		{
			ret = LoadTilesetImage(tileset, set);
		}

		data.tilesets.add(set);
	}
	pugi::xml_node layer;
	for (layer = map_file.child("map").child("layer"); layer && ret; layer = layer.next_sibling("layer"))
	{
		map_layer* set = new map_layer();

		if (ret == true)
		{
			ret = LoadLayer(layer, set);
		}

		data.layers.add(set);
	}

	// TODO 4: Iterate all layers and load each of them
	// Load layer info ----------------------------------------------
	

	if(ret == true)
	{
		LOG("Successfully parsed map XML file: %s", file_name);
		LOG("width: %d height: %d", data.width, data.height);
		LOG("tile_width: %d tile_height: %d", data.tile_width, data.tile_height);

		p2List_item<TileSet*>* item = data.tilesets.start;
		while(item != NULL)
		{
			TileSet* s = item->data;
			LOG("Tileset ----");
			LOG("name: %s firstgid: %d", s->name.GetString(), s->firstgid);
			LOG("tile width: %d tile height: %d", s->tile_width, s->tile_height);
			LOG("spacing: %d margin: %d", s->spacing, s->margin);
			item = item->next;
		}

		// TODO 4: Add info here about your loaded layers
		// Adapt this vcode with your own variables
		
		p2List_item<map_layer*>* item_layer = data.layers.start;
		while(item_layer != NULL)
		{
			map_layer* l = item_layer->data;
			LOG("Layer ----");
			LOG("name: %s", l->name.GetString());
			LOG("tile width: %d tile height: %d", l->width, l->height);
			item_layer = item_layer->next;
		}
	}

	map_loaded = ret;

	return ret;
}

// Load map general properties
bool j1Map::LoadMap()
{
	bool ret = true;
	pugi::xml_node map = map_file.child("map");

	if(map == NULL)
	{
		LOG("Error parsing map xml file: Cannot find 'map' tag.");
		ret = false;
	}
	else
	{
		data.width = map.attribute("width").as_int();
		data.height = map.attribute("height").as_int();
		data.tile_width = map.attribute("tilewidth").as_int();
		data.tile_height = map.attribute("tileheight").as_int();
		p2SString bg_color(map.attribute("backgroundcolor").as_string());

		data.background_color.r = 0;
		data.background_color.g = 0;
		data.background_color.b = 0;
		data.background_color.a = 0;

		if(bg_color.Length() > 0)
		{
			p2SString red, green, blue;
			bg_color.SubString(1, 2, red);
			bg_color.SubString(3, 4, green);
			bg_color.SubString(5, 6, blue);

			int v = 0;

			sscanf_s(red.GetString(), "%x", &v);
			if(v >= 0 && v <= 255) data.background_color.r = v;

			sscanf_s(green.GetString(), "%x", &v);
			if(v >= 0 && v <= 255) data.background_color.g = v;

			sscanf_s(blue.GetString(), "%x", &v);
			if(v >= 0 && v <= 255) data.background_color.b = v;
		}

		p2SString orientation(map.attribute("orientation").as_string());

		if(orientation == "orthogonal")
		{
			data.type = MAPTYPE_ORTHOGONAL;
		}
		else if(orientation == "isometric")
		{
			data.type = MAPTYPE_ISOMETRIC;
		}
		else if(orientation == "staggered")
		{
			data.type = MAPTYPE_STAGGERED;
		}
		else
		{
			data.type = MAPTYPE_UNKNOWN;
		}
	}

	return ret;
}

bool j1Map::LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;
	set->name.create(tileset_node.attribute("name").as_string());
	set->firstgid = tileset_node.attribute("firstgid").as_int();
	set->tile_width = tileset_node.attribute("tilewidth").as_int();
	set->tile_height = tileset_node.attribute("tileheight").as_int();
	set->margin = tileset_node.attribute("margin").as_int();
	set->spacing = tileset_node.attribute("spacing").as_int();
	pugi::xml_node offset = tileset_node.child("tileoffset");

	if(offset != NULL)
	{
		set->offset_x = offset.attribute("x").as_int();
		set->offset_y = offset.attribute("y").as_int();
	}
	else
	{
		set->offset_x = 0;
		set->offset_y = 0;
	}

	return ret;
}

bool j1Map::LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;
	pugi::xml_node image = tileset_node.child("image");

	if(image == NULL)
	{
		LOG("Error parsing tileset xml file: Cannot find 'image' tag.");
		ret = false;
	}
	else
	{
		set->texture = App->tex->Load(PATH(folder.GetString(), image.attribute("source").as_string()));
		int w, h;
		SDL_QueryTexture(set->texture, NULL, NULL, &w, &h);
		set->tex_width = image.attribute("width").as_int();

		if(set->tex_width <= 0)
		{
			set->tex_width = w;
		}

		set->tex_height = image.attribute("height").as_int();

		if(set->tex_height <= 0)
		{
			set->tex_height = h;
		}

		set->num_tiles_width = set->tex_width / set->tile_width;
		set->num_tiles_height = set->tex_height / set->tile_height;
	}

	return ret;
}

//TODO 3: Create the definition for a function that loads a single layer
bool j1Map::LoadLayer(pugi::xml_node& node, map_layer* layer)
{
	bool ret= true;
	layer->name = node.attribute("name").as_string();
	layer->width = node.attribute("width").as_uint();
	layer->height = node.attribute("height").as_uint();
	layer->size = layer->width*layer->height;

	layer->data = new uint[layer->size];

	memset(layer->data, 0, sizeof(uint)*(layer->size));
	pugi::xml_node data_node = node.child("data").first_child();

	for (uint i = 0; i<layer->size; i++)
	{
		layer->data[i] = data_node.attribute("gid").as_uint();
		data_node = data_node.next_sibling();
		//LOG("item # %d , number %d", i,layer->data[i]);
	}
	layer->logic_layer = node.child("properties").child("property").attribute("value").as_bool(false);
	if (layer->logic_layer)
	{
		CreateColliders(layer);
	}
	return ret;
}

bool j1Map::CreateColliders(map_layer* layer)
{
	int j = 0;
	data.colliders[j] = App->collision->AddCollider({-33,0,35,layer->height*35}, COLLIDER_WALL); ++j;
	data.colliders[j] = App->collision->AddCollider({ layer->width*35-1, 0, 35, layer->height * 35 }, COLLIDER_WALL); ++j;
		for (int _y = 0; _y < layer->height; ++_y)
		{
			for (int _x = 0; _x < layer->width; ++_x)
			{
				int i =layer->Get(_x, _y);
				iPoint point = MapToWorld(_x, _y);
				SDL_Rect rect;
				rect.x = point.x;
				rect.y = point.y;
				rect.w = 35;//WE WILL HAVE TO CHANGE THIS
				rect.h = 35;//WE WILL HAVE TO CHANGE THIS TOO

				SDL_Rect recthalf;
				recthalf.x = point.x;
				recthalf.y = point.y;
				recthalf.w = 35;
				recthalf.h = 20;

				switch (layer->data[i])
				{
				case 26:
					if (data.colliders[j] == nullptr)
						data.colliders[j] = App->collision->AddCollider(rect, COLLIDER_NEXT_LEVEL);
					j++;
					break;
				case 27:
					if (data.colliders[j] == nullptr)
						data.colliders[j] = App->collision->AddCollider(rect, COLLIDER_WALL);
					j++;
					break;
				case 28:
					if (data.colliders[j] == nullptr)
						data.colliders[j] = App->collision->AddCollider(recthalf, COLLIDER_WALL);
					j++;
					break;
				case 40:
					App->player->initial_x = point.x;
					App->player->initial_y = point.y;
					break;
				case 41:
					if (data.colliders[j] == nullptr)
						data.colliders[j] = App->collision->AddCollider(rect, COLLIDER_LAVA);
					j++;
					break;
				default:
					break;
				}
			}
		}

	

	return true;
}
void j1Map::change_map(uint map)
{
	index_map = map;
	CleanUp();
	Load(maps[index_map].GetString());
	App->player->SetPosOrigin();
}
void j1Map::next_level()
{
	index_map += 1;
	CleanUp();
	Load(maps[index_map].GetString());
	App->player->SetPosOrigin();
}