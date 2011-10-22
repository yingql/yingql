package com.yingql.android.games.zhaocha.layer;

import android.view.MotionEvent;

import com.wiyun.engine.nodes.INodeVirtualMethods;
import com.wiyun.engine.nodes.Layer;
import com.wiyun.engine.nodes.Sprite;
import com.wiyun.engine.opengl.Texture2D;
import com.wiyun.engine.types.WYPoint;
import com.wiyun.engine.types.WYRect;
import com.wiyun.engine.utils.ResolutionIndependent;
import com.yingql.android.games.zhaocha.core.GameStrategy;
import com.yingql.android.games.zhaocha.entity.GameInfo;
import com.yingql.android.games.zhaocha.entity.LevelInfo;
import com.yingql.android.games.zhaocha.sprite.Pieces;

public class GameLayer extends Layer implements INodeVirtualMethods
{
	public static final float BaseX = 0;
	public static final float BaseX2 = 200;
	public static final float BaseY = 54;
	public static final float ImageHeight = 262;
	public static final float Scale = 2f / 3f;
	public static final int TAG_IMAGE = 1;
	public static final int BUTTON_ZINDEX = 0;
	public static final int PIECE_ZINDEX = -1;
	public static final int IMAGE_ZINDEX = -2;

	private Pieces pieces;
	private WYRect clickArea;

	public GameLayer()
	{
		pieces = new Pieces(this);
		clickArea = ResolutionIndependent.resolve(WYRect.make(0, BaseY, 400, ImageHeight));
		this.setJavaVirtualMethods(this);
		this.setTouchEnabled(true);		
	}

	public void initMap(GameInfo gameInfo)
	{
		this.removeAllChildren(true);

		LevelInfo info = gameInfo.getLevelInfo();

		Sprite leftImage = Sprite.make(Texture2D.makeJPG(info.getResPath()));
		leftImage.setAnchorPercent(0, 0);
		leftImage.setPosition(ResolutionIndependent.resolve(WYPoint.make(BaseX, BaseY)));
		this.addChild(leftImage, IMAGE_ZINDEX, TAG_IMAGE);
		leftImage.autoRelease();

		Sprite rightImage = Sprite.make(Texture2D.makeJPG(info.getResPath()));
		rightImage.setAnchorPercent(0, 0);
		rightImage.setPosition(ResolutionIndependent.resolve(WYPoint.make(BaseX2, BaseY)));
		this.addChild(rightImage, IMAGE_ZINDEX, TAG_IMAGE);
		rightImage.autoRelease();

		pieces.init(info);
	}

	@Override
	public boolean wyTouchesBegan(MotionEvent event)
	{
		// 触摸点在图片外的不应该计算入内
		if (clickArea.containsPoint(this.convertTouchToNodeSpace(event)))
		{
			boolean isHit = pieces.touch(event);
			GameStrategy.clickPiece(isHit);
			return isHit;
		}
		return false;
	}

	@Override
	public void jDraw()
	{
		pieces.drawRectIfFind();
	}

	@Override
	public void jOnEnter()
	{
	}

	@Override
	public void jOnEnterTransitionDidFinish()
	{
	}

	@Override
	public void jOnExit()
	{
	}

	public Pieces getPieces()
	{
		return pieces;
	}
}
