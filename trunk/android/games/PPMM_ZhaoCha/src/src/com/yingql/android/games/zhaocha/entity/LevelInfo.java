package com.yingql.android.games.zhaocha.entity;

import java.util.ArrayList;
import java.util.List;

public class LevelInfo
{
	private int imageIndex = 0;
	private String resPath = "";
	private List<PieceInfo> pieces = new ArrayList<PieceInfo>();

	public int getImageIndex()
	{
		return imageIndex;
	}

	public void setImageIndex(int imageIndex)
	{
		this.imageIndex = imageIndex;
	}

	public String getResPath()
	{
		return resPath;
	}

	public void setResPath(String resPath)
	{
		this.resPath = resPath;
	}

	public List<PieceInfo> getPieces()
	{
		return pieces;
	}

	/**
	 * 获取所有Pieces的下标，用|分割
	 * 
	 * @return
	 */
	public String getPiecesIndex()
	{
		String result = "";
		for (PieceInfo piece : pieces)
		{
			result += piece.getImageIndex() + Archive.SPLIT_CHAR;
		}
		if (result.length() > 0)
		{
			result = result.substring(0, result.length() - 1);
		}
		return result;
	}
}
