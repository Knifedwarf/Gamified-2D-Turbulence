#include "GameState.h"

#include <string>
#include <iostream>
#include <iomanip>


GameState::GameState()
{
}


GameState::~GameState()
{

}

void GameState::Create(int p_gridx, int p_gridy)
{
	//setting grid size
	totalvolume = 0;
	m_numberofcells[0] = p_gridx;
	m_numberofcells[1] = p_gridy;

	//creating cells
	m_cells = new Cell*[p_gridx];

	for(int i = 0; i < m_numberofcells[0]; i++)
	{
		m_cells[i] = new Cell[p_gridy];
	}

	//positioning cells
	for (int i = 0; i < m_numberofcells[0]; i++)
	{
		for (int j = 0; j < m_numberofcells[1]; j++)
		{
			m_cells[i][j].x = i*5;
			m_cells[i][j].y = j*5;
			m_cells[i][j].w = 5;
			m_cells[i][j].h = 5;
		}
	}

	//giving cells neighbour contact (initialization)
	for (int i = 0; i < m_numberofcells[0]; i++)
	{
		for (int j = 0; j < m_numberofcells[1]; j++)
			{
				Cell* tempcells[4];
				if (i == 0)
				{
					tempcells[3] = nullptr;
				}
				else 
				{
					tempcells[3] = &m_cells[i - 1][j];
				}

				if (i == m_numberofcells[0]-1)
				{
					tempcells[1] = nullptr;
				}
				else
				{
					tempcells[1] = &m_cells[i + 1][j];
				}

				if (j == 0)
				{
					tempcells[0] = nullptr;
				}
				else
				{
					tempcells[0] = &m_cells[i][j-1];
				}

				if (j == m_numberofcells[1] - 1)
				{
					tempcells[2] = nullptr;
				}
				else
				{
					tempcells[2] = &m_cells[i][j+1];
				}

				m_cells[i][j].Initialize(tempcells[0], tempcells[1], tempcells[2], tempcells[3]);
				
			}

	}
}

void GameState::Initialize() 
{
	Create(20, 20);
}

void GameState::Update(double deltatime) 
{
	
	totalvolume = 0;

	for (int i = 0; i < m_numberofcells[0]; i++)
	{
		for (int j = 0; j < m_numberofcells[1]; j++)
		{


			m_cells[i][j].EarlyUpdate(deltatime);


		}
	}
	
	for (int i = 0; i < m_numberofcells[0]; i++)
	{
		for (int j = 0; j < m_numberofcells[1]; j++)
		{
			
			
			m_cells[i][j].Update(deltatime);
			
			
		}
	}

	float hey = 0;
	
	for (int i = 0; i < m_numberofcells[0]; i++)
	{
		for (int j = 0; j < m_numberofcells[1]; j++)
		{


			
			totalvolume += m_cells[i][j].m_water;

		}
	}
	std::cout << std::fixed << std::setprecision(5) << totalvolume << std::endl;
	
	LateUpdate();
	
	for (int i = 0; i < m_numberofcells[0]; i++)
	{
		for (int j = 0; j < m_numberofcells[1]; j++)
		{

			m_cells[i][j].LateUpdate(deltatime);
			std::cout << std::fixed << std::setprecision(10) << m_cells[i][j].m_total_pressure << std::endl;
		}
	}
	
	for (int i = 0; i < m_numberofcells[0]; i++)
	{
		for (int j = 0; j < m_numberofcells[1]; j++)
		{
			

			m_cells[i][j].LateUpdate2(deltatime);
			
			
		}
	}
	
	for (int i = 0; i < m_numberofcells[0]; i++)
	{
		for (int j = 0; j < m_numberofcells[1]; j++)
		{
			

			//m_cells[i][j].LateUpdate3(deltatime);


		}
	}
}

void GameState::LateUpdate()
{
	
	
	

}

void GameState::Draw(DrawManager& p_DrawManager) 
{
	for (int i = 0; i < m_numberofcells[0]; i++)
	{
		for (int j = 0; j < m_numberofcells[1]; j++)
		{
			p_DrawManager.Draw(m_cells[i][j]);
		}
	}
}

void GameState::Exit() 
{
	for (int i = 0; i < m_numberofcells[0]; i++)
	{
		delete[] m_cells[i];
	}
	delete[] m_cells;
}
