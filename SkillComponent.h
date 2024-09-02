#pragma once

enum SKILLS {HEALTH = 0, ATTACK, ACCURACY, ENDURANCE};

class SkillComponent
{
private:
	class Skill
	{
	private:
		int type;
		int level;
		int levelCap;
		int exp;
		int expNext;

	public:
		Skill(int type)
		{
			this->type = type;
			this->levelCap = 99;
			this->level = 1;
			this->exp = 0;
			this->expNext = 100;
		}
		~Skill() {}

		// Accessors
		inline const int& getType() const { return this->type; }
		inline const int& getLevel() const { return this->level; }
		inline const int& getExp() const { return this->exp; }
		inline const int& getExpNext() const { return this->expNext; }

		// Modifiers
		inline void setLevel(const int level) { this->level = level; }
		inline void setLevelCap(const int level_cap) { this->levelCap = level_cap; }

		void gainExp(const int exp) 
		{ 
			this->exp += exp;
			updateLevel(); 
		}
		void loseExp(const int exp)
		{
			this->exp -= exp;
		}

		// Functions
		void updateLevel(const bool up = true)
		{
			/*
			* 
			* Increases or Decreases the level of the skill depending on if there is a deficit in exp or not.
			* 
			*/

			if (up)
			{
				if (level < levelCap)
				{
					while (exp >= expNext)
					{
						if (level < levelCap)
						{
							level++;
							expNext = static_cast<int>(std::pow(level, 2)) + (level * 10) + (level * 2);
						}
					}
				}
			}
			else
			{
				if (level > 0)
				{
					while (exp < 0)
					{
						if (level > 0)
						{
							level--;
							expNext = static_cast<int>(std::pow(level, 2)) + (level * 10) + (level * 2);
						}
					}
				}
			}
		}
		void update() 
		{
			updateLevel();
		}

	};

	// Variables
	std::vector<Skill> skills;

	// init functions
	void initSkills();

public:
	SkillComponent();
	virtual ~SkillComponent();

	// Accessors
	const int getSkill(const int skill) const;
	

	// Functions
	const void gainExp(const int skill, const int exp);
};

