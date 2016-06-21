#include "Crystal.h"
#include "Model.h"
#include "Player.h"


Crystal::Crystal(const std::string & filled, const std::string & empty, const Vec3f & position, Vec3f & rotation, const float & scale)
{
	this->filled = Model::load(filled);
	this->empty = Model::load(empty);
	model = this->filled;	

	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
	this->canCollide = true;
	isFilled = true;

	sound_id = CrystalPoint::GetSoundSystem().LoadSound("WAVE/Crystal.wav", false);
	music = CrystalPoint::GetSoundSystem().GetSound(sound_id);
	music->SetPos(position, Vec3f());
}

Crystal::~Crystal()
{
	CrystalPoint::GetSoundSystem().UnloadSound(sound_id);
	if (model)
		Model::unload(model);

	//if isfilled, means model is model filled, so model empty has to been deleted.
	//if is not filled, means model is model empty, so model filled has to been deleted.
	if (isFilled)
		if(empty)
			Model::unload(empty);
	else
		if(filled)
			Model::unload(filled);
}

void Crystal::draw()
{	
	Entity::draw();	
}

void Crystal::collide()
{
	if (isFilled)
	{
		music->Play();
		Player::getInstance()->crystals++;
		isFilled = false;
		model = empty;
	}	
}
