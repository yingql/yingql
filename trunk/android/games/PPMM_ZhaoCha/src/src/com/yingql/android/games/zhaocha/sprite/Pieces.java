package com.yingql.android.games.zhaocha.sprite;

import java.util.ArrayList;
import java.util.List;

import android.view.MotionEvent;

import com.wiyun.engine.nodes.Node;
import com.yingql.android.games.zhaocha.entity.Archive;
import com.yingql.android.games.zhaocha.entity.LevelInfo;
import com.yingql.android.games.zhaocha.entity.PieceInfo;
import com.yingql.android.games.zhaocha.layer.GameLayer;

public class Pieces extends Node
{
	private GameLayer layer;
	private List<Piece> pieces = new ArrayList<Piece>();

	public Pieces(GameLayer layer)
	{
		this.layer = layer;
	}

	public void init(LevelInfo levelInfo)
	{
		pieces.clear();
		for (PieceInfo pieceInfo : levelInfo.getPieces())
		{
			Piece piece = new Piece(pieceInfo);
			piece.setAnchorPercent(0, 0);
			layer.addChild(piece, GameLayer.PIECE_ZINDEX);
			piece.autoRelease();
			pieces.add(piece);
		}
	}

	/**
	 * 为找到的茬周围画上红色的矩形
	 */
	public void drawRectIfFind()
	{
		List<Piece> temp = new ArrayList<Piece>(pieces);
		for (Piece piece : temp)
		{
			if (piece.isFind())
			{
				piece.drawRect();
			}
		}
	}

	/**
	 * 获取还没有被找到的茬的数量
	 * 
	 * @return
	 */
	public int getRemainPieceCount()
	{
		int count = 0;
		for (Piece piece : pieces)
		{
			if (!piece.isFind())
				count++;
		}
		return count;
	}

	/**
	 * 随机找到一个还没有被找到的茬
	 * 
	 * @return 返回是否找到了这样的茬
	 */
	public boolean findRandomPiece()
	{
		for (Piece piece : pieces)
		{
			if (!piece.isFind())
			{
				piece.setFind(true);
				return true;
			}
		}
		return false;
	}

	/**
	 * 触摸界面
	 * 
	 * @param event
	 * @return
	 */
	public boolean touch(MotionEvent event)
	{
		boolean isHit = false;
		if (this.layer.isTouchEnabled())
		{
			for (Piece piece : pieces)
			{
				if (piece.isHit(event))
				{
					isHit = true;
					break;
				}
			}
		}
		return isHit;
	}

	/**
	 * 获取所有已经找到的Pieces的下标
	 * 
	 * @return
	 */
	public String getFoundPiecesIndex()
	{
		String result = "";
		for (Piece piece : pieces)
		{
			if (piece.isFind())
			{
				result += piece.getIndex() + Archive.SPLIT_CHAR;
			}
		}
		if (result.length() > 0)
		{
			result = result.substring(0, result.length() - 1);
		}
		return result;
	}
}
