// This work by Matheus Vilano is licensed under Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/

#include "BinoraGameModeBase.h"

#pragma region Constructors

    ABinoraGameModeBase::ABinoraGameModeBase(){}

#pragma endregion

#pragma region Framework

    void ABinoraGameModeBase::BeginPlay()
    {
        // GET ALL ACTORS OF TYPE <>
        // COUNT THEM
        // MULTIPLY BY 3
        // SET MAXSCORE
    }

#pragma endregion

#pragma region Score

    inline void ABinoraGameModeBase::AddScore(uint8 Addend)
    {
        this->Score = ((this->Score + Addend) > 100) ? 100 : this->Score + Addend;
    }

    float ABinoraGameModeBase::GetScoreAsPercentage() const
    {
        return 100 * this->Score / this->MaxScore;
    }

    EScoreCategory ABinoraGameModeBase::GetScoreAsCategory() const
    {
        // This will be used to get the score as a category
        uint8 ScoreAsPercentage = this->GetScoreAsPercentage();

        // Subpar
        if (ScoreAsPercentage < EScoreCategory::SC_Good)
        {
            return EScoreCategory::SC_Subpar;
        }
        // Good
        else if (ScoreAsPercentage < EScoreCategory::SC_Great)
        {
            return EScoreCategory::SC_Good;
        }
        // Great
        else if (ScoreAsPercentage < EScoreCategory::SC_Perfect)
        {
            return EScoreCategory::SC_Great;
        }
        // Perfect
        else // if the user got a perfect score (100%)
        {
            return EScoreCategory::SC_Perfect;
        }
    }

#pragma endregion