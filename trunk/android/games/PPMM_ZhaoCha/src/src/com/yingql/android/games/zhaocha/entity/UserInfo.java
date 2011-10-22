package com.yingql.android.games.zhaocha.entity;

public class UserInfo
{
	private int id = -1;
	private String userName = "default";
	private int coins = 500;
	private boolean isMusicOn = true;
	private int quickGameHighScore = 0;
	private int timelessHighScore = 0;
	private int quickGameMaxLevel = 0;
	private int timelessMaxLevel = 0;
	private int findItemCount = 0;
	private int clockItemCount = 0;

	public int getId()
	{
		return id;
	}

	public void setId(int id)
	{
		this.id = id;
	}

	public String getUserName()
	{
		return userName;
	}

	public void setUserName(String userName)
	{
		this.userName = userName;
	}

	public int getCoins()
	{
		return coins;
	}

	public void setCoins(int coins)
	{
		this.coins = coins;
	}

	public boolean isMusicOn()
	{
		return isMusicOn;
	}

	public void setMusicOn(boolean isMusicOn)
	{
		this.isMusicOn = isMusicOn;
	}

	public int getQuickGameHighScore()
	{
		return quickGameHighScore;
	}

	public void setQuickGameHighScore(int quickGameHighScore)
	{
		this.quickGameHighScore = quickGameHighScore;
	}

	public int getTimelessHighScore()
	{
		return timelessHighScore;
	}

	public void setTimelessHighScore(int timelessHighScore)
	{
		this.timelessHighScore = timelessHighScore;
	}

	public int getQuickGameMaxLevel()
	{
		return quickGameMaxLevel;
	}

	public void setQuickGameMaxLevel(int quickGameMaxLevel)
	{
		this.quickGameMaxLevel = quickGameMaxLevel;
	}

	public int getTimelessMaxLevel()
	{
		return timelessMaxLevel;
	}

	public void setTimelessMaxLevel(int timelessMaxLevel)
	{
		this.timelessMaxLevel = timelessMaxLevel;
	}

	public int getFindItemCount()
	{
		return findItemCount;
	}

	public void setFindItemCount(int findItemCount)
	{
		this.findItemCount = findItemCount;
	}

	public int getClockItemCount()
	{
		return clockItemCount;
	}

	public void setClockItemCount(int clockItemCount)
	{
		this.clockItemCount = clockItemCount;
	}
}
