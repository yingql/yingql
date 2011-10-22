package com.yingql.android.games.zhaocha.entity;

import java.util.ArrayList;
import java.util.List;

/**
 * 存档实体
 * 
 * @author yingql
 * 
 */
public class Archive
{
	private float remainTime;
	private int score;
	private int curCombo;
	private int maxCombo;
	private int levelCount;
	private int mapIndex;
	private int clickCount = 0;
	private int rightCount = 0;
	private List<Integer> pieces;
	private List<Integer> foundPieces;
	public static final String SPLIT_CHAR = ",";

	public float getRemainTime()
	{
		return remainTime;
	}

	public void setRemainTime(float remainTime)
	{
		this.remainTime = remainTime;
	}

	public int getScore()
	{
		return score;
	}

	public void setScore(int score)
	{
		this.score = score;
	}

	public int getCurCombo()
	{
		return curCombo;
	}

	public void setCurCombo(int curCombo)
	{
		this.curCombo = curCombo;
	}

	public int getMaxCombo()
	{
		return maxCombo;
	}

	public void setMaxCombo(int maxCombo)
	{
		this.maxCombo = maxCombo;
	}

	public int getLevelCount()
	{
		return levelCount;
	}

	public void setLevelCount(int levelCount)
	{
		this.levelCount = levelCount;
	}

	public int getMapIndex()
	{
		return mapIndex;
	}

	public void setMapIndex(int mapIndex)
	{
		this.mapIndex = mapIndex;
	}

	public List<Integer> getPieces()
	{
		return pieces;
	}

	public void setPieces(List<Integer> pieces)
	{
		this.pieces = pieces;
	}

	public void setPieces(String source)
	{
		String[] pieces = source.split(Archive.SPLIT_CHAR);
		List<Integer> temp = new ArrayList<Integer>();
		for (int i = 0; i < pieces.length; i++)
		{
			temp.add(Integer.parseInt(pieces[i]));
		}
		this.pieces = temp;
	}

	public List<Integer> getFoundPieces()
	{
		return foundPieces;
	}

	public void setFoundPieces(List<Integer> foundPieces)
	{
		this.foundPieces = foundPieces;
	}

	public void setFoundPieces(String source)
	{
		String[] pieces = source.split(Archive.SPLIT_CHAR);
		List<Integer> temp = new ArrayList<Integer>();
		if (source != null && source.length() > 0)
		{
			for (int i = 0; i < pieces.length; i++)
			{
				temp.add(Integer.parseInt(pieces[i]));
			}
		}
		this.foundPieces = temp;
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
}
