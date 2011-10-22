package com.yingql.android.games.zhaocha.sprite;

import javax.microedition.khronos.opengles.GL10;

import android.view.MotionEvent;

import com.wiyun.engine.nodes.Director;
import com.wiyun.engine.nodes.Node;
import com.wiyun.engine.nodes.Sprite;
import com.wiyun.engine.opengl.Primitives;
import com.wiyun.engine.opengl.Texture2D;
import com.wiyun.engine.types.WYPoint;
import com.wiyun.engine.types.WYRect;
import com.wiyun.engine.utils.ResolutionIndependent;
import com.yingql.android.games.zhaocha.entity.PieceInfo;
import com.yingql.android.games.zhaocha.layer.GameLayer;

public class Piece extends Node
{
	private WYRect touchRectLeft, touchRectRight;
	private boolean isFind = false;
	private static int ZINDEX = -1;
	private int index = 1;

	public Piece(PieceInfo info)
	{
		isFind = info.isFind();
		index = info.getImageIndex();
		WYPoint point = WYPoint.make(GameLayer.BaseX + info.x * GameLayer.Scale, GameLayer.BaseY + GameLayer.ImageHeight - (info.y + info.height)
				* GameLayer.Scale);

		Texture2D tex = Texture2D.makeJPG(info.getResPath());
		tex.setAntiAlias(false);
		Sprite cha = Sprite.make(tex);
		cha.setAnchorPercent(0, 0);
		cha.setPosition(ResolutionIndependent.resolve(point));
		this.addChild(cha, ZINDEX);
		cha.autoRelease();

		// TODO 由于现在计算的坐标是针对hdpi的，所以这里先转换成mdpi的值
		float x = GameLayer.BaseX + info.x * GameLayer.Scale;
		float x2 = GameLayer.BaseX2 + info.x * GameLayer.Scale;
		float y = GameLayer.BaseY + GameLayer.ImageHeight - (info.y + info.height) * GameLayer.Scale;
		touchRectLeft = ResolutionIndependent.resolve(WYRect.make(x, y, info.width * GameLayer.Scale, info.height * GameLayer.Scale));
		touchRectRight = ResolutionIndependent.resolve(WYRect.make(x2, y, info.width * GameLayer.Scale, info.height * GameLayer.Scale));
	}

	/**
	 * 是否命中
	 * 
	 * @param event
	 * @return
	 */
	public boolean isHit(MotionEvent event)
	{
		if (touchRectLeft.containsPoint(this.convertTouchToNodeSpace(event)) || touchRectRight.containsPoint(this.convertTouchToNodeSpace(event)))
		{
			if (!this.isFind)
			{
				this.isFind = true;
				return true;
			}
		}
		return false;
	}

	public void drawRect()
	{
		if (this.isFind)
		{
			GL10 gl = Director.getInstance().gl;
			gl.glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
			Primitives.drawRect(touchRectLeft);
			Primitives.drawRect(touchRectRight);
			gl.glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

	public boolean isFind()
	{
		return isFind;
	}

	public void setFind(boolean isFind)
	{
		this.isFind = isFind;
	}

	public int getIndex()
	{
		return index;
	}

	public void setIndex(int index)
	{
		this.index = index;
	}
}
