package com.yingql.android.games.zhaocha.layer;

import com.wiyun.engine.actions.Action;
import com.wiyun.engine.actions.Animate;
import com.wiyun.engine.actions.CallFunc;
import com.wiyun.engine.actions.RepeatForever;
import com.wiyun.engine.nodes.Animation;
import com.wiyun.engine.nodes.ColorLayer;
import com.wiyun.engine.nodes.Sprite;
import com.wiyun.engine.opengl.Texture2D;
import com.wiyun.engine.types.WYColor4B;
import com.wiyun.engine.types.WYPoint;
import com.yingql.android.games.zhaocha.R;
import com.yingql.android.games.zhaocha.core.GameSystem;
import com.yingql.android.games.zhaocha.scene.StartScene;
import com.yingql.android.games.zhaocha.util.GameUtil;

public class GameLoadingLayer extends ColorLayer
{
	public GameLoadingLayer()
	{
		super(WYColor4B.make(255, 255, 255, 255));
		// 显示loading动画
		Animation animation = new Animation(0, 0.3f, R.drawable.loading_0, R.drawable.loading_1, R.drawable.loading_2, R.drawable.loading_3,
				R.drawable.loading_4, R.drawable.loading_5, R.drawable.loading_6);
		animation.autoRelease();
		Animate animate = Animate.make(animation);
		animate.autoRelease();

		Sprite sprite = Sprite.make(R.drawable.loading_0);
		addChild(sprite);
		sprite.setPosition(GameSystem.Screen_Width / 2, GameSystem.Screen_Height / 2);
		sprite.autoRelease();

		sprite.runAction((Action) RepeatForever.make(animate).autoRelease());
		sprite.runAction((CallFunc) CallFunc.make(this, "loadResource").autoRelease());
		
		Sprite logo = Sprite.make(Texture2D.makeJPG(R.drawable.wiyun_logo));
		addChild(logo);
		logo.setAnchorPercent(1, 0);
		logo.setPosition(WYPoint.make(GameSystem.Screen_Width, 0));
		logo.autoRelease();
	}

	/**
	 * 加载系统资源
	 */
	public void loadResource()
	{
		new Thread()
		{
			public void run()
			{
				try
				{
					Thread.sleep(500);
				}
				catch (InterruptedException e)
				{
					e.printStackTrace();
				}
				GameSystem.loadAllResource();
				try
				{
					Thread.sleep(500);
				}
				catch (InterruptedException e)
				{
					e.printStackTrace();
				}
				gotoGameMenu();
			}
		}.start();
	}

	/**
	 * 切换到游戏菜单
	 */
	public void gotoGameMenu()
	{
		GameUtil.switchScene(StartScene.make());
		StartScene.getInstance().init();
	}
}
