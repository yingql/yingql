package com.yingql.android.games.zhaocha.entity;

import com.wiyun.engine.types.WYRect;

public class PieceInfo
{
	private String resPath;
	private int imageIndex = 1;
	private WYRect rect = null;
	public float x, y, width, height;
	private boolean isFind = false;

	public String getResPath()
	{
		return resPath;
	}

	public void setResPath(String resPath)
	{
		this.resPath = resPath;
	}

	public float getX()
	{
		return x;
	}

	public void setX(float x)
	{
		this.x = x;
	}

	public float getY()
	{
		return y;
	}

	public void setY(float y)
	{
		this.y = y;
	}

	public float getWidth()
	{
		return width;
	}

	public void setWidth(float width)
	{
		this.width = width;
	}

	public float getHeight()
	{
		return height;
	}

	public void setHeight(float height)
	{
		this.height = height;
	}

	public WYRect getRect()
	{
		if (rect == null)
		{
			rect = WYRect.make(x, y, width, height);
		}
		return this.rect;
	}

	public int getImageIndex()
	{
		return imageIndex;
	}

	public void setImageIndex(int imageIndex)
	{
		this.imageIndex = imageIndex;
	}

	public boolean isFind()
	{
		return isFind;
	}

	public void setFind(boolean isFind)
	{
		this.isFind = isFind;
	}
}
