#include "stdafx.h"
#include "SkillComponent.h"

void SkillComponent::initSkills()
{
	skills.push_back(Skill(HEALTH));
	skills.push_back(Skill(ATTACK));
	skills.push_back(Skill(ACCURACY));
	skills.push_back(Skill(ENDURANCE));
}

SkillComponent::SkillComponent()
{
	initSkills();
}

SkillComponent::~SkillComponent()
{

}

const int SkillComponent::getSkill(const int skill) const
{
	if (skills.empty() || skill < 0 || skill >= skills.size())
	{
		throw("ERROR::SKILLCOMPONENT::GETSKILL::SKILL_DOES_NOT_EXIST: " + skill);
	}
	else
		return skills[skill].getLevel();
}

const void SkillComponent::gainExp(const int skill, const int exp)
{
	if (skills.empty() || skill < 0 || skill >= skills.size())
	{
		throw("ERROR::SKILLCOMPONENT::GAINEXP::SKILL_DOES_NOT_EXIST: " + skill);
	}
	else
	{
		skills[skill].gainExp(exp);
	}
}
