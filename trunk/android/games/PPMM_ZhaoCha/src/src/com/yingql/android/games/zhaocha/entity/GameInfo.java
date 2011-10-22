package com.yingql.android.games.zhaocha.entity;

import com.yingql.android.games.zhaocha.util.WiGameUtil;

public class GameInfo
{
	private GameMode mode = GameMode.QuickGame;
	private int levelCount = 0;
	private int highScore = 0;
	private int maxCombo = 0;
	private int curCombo = 0;
	private int curScore = 0;
	private float totalTime = 0;
	private LevelInfo levelInfo;
	private int findItemCount = 0;
	private int clockItemCount = 0;
	private boolean isNewRecord = false;
	private int clickCount = 0;
	private int rightCount = 0;
	private boolean isRunning = false;

	public GameMode getMode()
	{
		return mode;
	}

	public void setMode(GameMode mode)
	{
		this.mode = mode;
	}

	public int getHighScore()
	{
		return highScore;
	}

	public void setHighScore(int highScore)
	{
		this.highScore = highScore;
	}

	public int getMaxCombo()
	{
		return maxCombo;
	}

	public void setMaxCombo(int maxCombo)
	{
		this.maxCombo = maxCombo;
	}

	public int getCurCombo()
	{
		return curCombo;
	}

	public void setCurCombo(int curCombo)
	{
		this.curCombo = curCombo;
	}

	public int getCurScore()
	{
		return curScore;
	}

	public void setCurScore(int curScore)
	{
		this.curScore = curScore;
	}

	public float getTotalTime()
	{
		return totalTime;
	}

	public void setTotalTime(float totalTime)
	{
		this.totalTime = totalTime;
	}

	public LevelInfo getLevelInfo()
	{
		return levelInfo;
	}

	public void setLevelInfo(LevelInfo levelInfo)
	{
		this.levelInfo = levelInfo;
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

	public int getLevelCount()
	{
		return levelCount;
	}

	public void setLevelCount(int levelCount)
	{
		this.levelCount = levelCount;
	}

	public boolean isNewRecord()
	{
		return isNewRecord;
	}

	public void setNewRecord(boolean isNewRecord)
	{
		this.isNewRecord = isNewRecord;
	}

	public int getClickCount()
	{
		return clickCount;
	}

	public void setClickCount(int clickCount)
	{
		this.clickCount = clickCount;
	}

	public int getRightCount()
	{
		return rightCount;
	}

	public void setRightCount(int rightCount)
	{
		this.rightCount = rightCount;
	}

	public boolean isRunning()
	{
		return isRunning;
	}

	public void setRunning(boolean isRunning)
	{
		this.isRunning = isRunning;
	}

	public void addScore(int score)
	{
		this.curScore += score;
		// 更新最高分
		if (this.curScore > this.highScore)
		{
			this.highScore = this.curScore;
			this.isNewRecord = true;
			WiGameUtil.ScoreAchievement.unlockScoreAchievement(this.highScore);
		}
	}

	public void combo()
	{
		this.curCombo++;
		// 更新最大连击数
		if (this.curCombo > this.maxCombo)
		{
			this.maxCombo = this.curCombo;
			WiGameUtil.ComboAchievement.unlockComboAchievement(this.maxCombo);
		}
	}

	public void click(boolean right)
	{
		this.clickCount++;
		if (right)
			this.rightCount++;
	}

	/**
	 * 重置部分数据，以准备进行下次处理
	 */
	public void reset()
	{
		this.setCurScore(0);
		this.setCurCombo(0);
		this.setClickCount(0);
		this.setRightCount(0);
		this.setMaxCombo(0);
		this.setLevelCount(0);
		this.setRunning(false);
	}
}
