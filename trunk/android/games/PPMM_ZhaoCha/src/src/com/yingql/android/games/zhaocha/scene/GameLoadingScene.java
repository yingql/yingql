package com.yingql.android.games.zhaocha.scene;

import android.view.KeyEvent;

import com.wiyun.engine.nodes.Scene;
import com.yingql.android.games.zhaocha.MainActivity;
import com.yingql.android.games.zhaocha.layer.GameLoadingLayer;

public class GameLoadingScene extends Scene
{
	protected GameLoadingScene()
	{
		GameLoadingLayer layer = new GameLoadingLayer();
		layer.autoRelease(true);
		this.addChild(layer);
	}

	public static GameLoadingScene make()
	{
		GameLoadingScene scene = new GameLoadingScene();
		scene.autoRelease(true);
		return scene;
	}
	
	@Override
	public boolean wyKeyDown(KeyEvent event)
	{
		if (event.getKeyCode() == KeyEvent.KEYCODE_BACK)
		{
			MainActivity.Instance.showExitTips();
			return true;
		}
		return super.wyKeyDown(event);
	}
}