package com.yingql.android.games.zhaocha.scene;

import android.view.KeyEvent;

import com.wiyun.engine.nodes.Scene;
import com.yingql.android.games.zhaocha.entity.GameInfo;
import com.yingql.android.games.zhaocha.layer.BuyClockItemLayer;
import com.yingql.android.games.zhaocha.layer.BuyFindItemLayer;
import com.yingql.android.games.zhaocha.layer.GameBGLayer;
import com.yingql.android.games.zhaocha.layer.GameLayer;
import com.yingql.android.games.zhaocha.layer.GameOverLayer;
import com.yingql.android.games.zhaocha.layer.GamePauseLayer;
import com.yingql.android.games.zhaocha.util.ADHelper;
import com.yingql.android.games.zhaocha.util.GameUtil;

public class GameScene extends Scene
{
	private static GameScene scene = null;
	private static Object syncObj = new Object();

	private GameBGLayer gameBGLayer;
	private GameLayer gameLayer;
	private GameOverLayer gameOverLayer;
	private BuyFindItemLayer buyFindItemLayer;
	private BuyClockItemLayer buyClockItemLayer;
	private GamePauseLayer gamePauseLayer;

	protected GameScene()
	{
		gameBGLayer = new GameBGLayer();
		gameLayer = new GameLayer();
		gameOverLayer = new GameOverLayer();
		buyFindItemLayer = new BuyFindItemLayer();
		buyClockItemLayer = new BuyClockItemLayer();
		gamePauseLayer = new GamePauseLayer();
		this.addChild(gameBGLayer, 1);
		this.addChild(gameLayer, 2);
		this.addChild(gameOverLayer, 3);
		this.addChild(buyFindItemLayer, 4);
		this.addChild(buyClockItemLayer, 4);
		this.addChild(gamePauseLayer, 5);
		this.gameOverLayer.setVisible(false);
		this.buyFindItemLayer.setVisible(false);
		this.buyClockItemLayer.setVisible(false);
		this.gamePauseLayer.setVisible(false);
	}

	public static GameScene getInstance()
	{
		return make();
	}

	public static GameScene make()
	{
		if (scene == null)
		{
			synchronized (syncObj)
			{
				if (scene == null)
				{
					scene = new GameScene();
					scene.autoRelease(true);
				}
			}
		}
		return scene;
	}

	public GameBGLayer getGameBGLayer()
	{
		return gameBGLayer;
	}

	public GameLayer getGameLayer()
	{
		return gameLayer;
	}

	public GameOverLayer getGameOverLayer()
	{
		return gameOverLayer;
	}

	public BuyFindItemLayer getBuyFindItemLayer()
	{
		return buyFindItemLayer;
	}

	public BuyClockItemLayer getBuyClockItemLayer()
	{
		return buyClockItemLayer;
	}

	/**
	 * 开始游戏
	 * 
	 * @param gameInfo
	 */
	public void startGame(GameInfo gameInfo)
	{
		this.gameOverLayer.setVisible(false);
		this.buyFindItemLayer.setVisible(false);
		this.buyClockItemLayer.setVisible(false);
		this.gamePauseLayer.setVisible(false);
		this.gameBGLayer.init(gameInfo);
		this.gameLayer.initMap(gameInfo);
		enableTouch();
		this.gameBGLayer.getBoard().startTimer();
		ADHelper.showAd();
	}

	/**
	 * 时间到，游戏结束
	 */
	public void endGame()
	{
		ADHelper.hideAd();
		disableTouch();
		this.gameOverLayer.init();
		this.gameOverLayer.setVisible(true);
	}

	public void showBuyFindItemLayer()
	{
		disableTouch();
		this.gameBGLayer.getBoard().stopTimer();
		this.buyFindItemLayer.setVisible(true);
	}

	public void hideBuyFindItemLayer()
	{
		enableTouch();
		this.gameBGLayer.getBoard().startTimer();
		this.buyFindItemLayer.setVisible(false);
	}

	public void showBuyClockItemLayer()
	{
		disableTouch();
		this.gameBGLayer.getBoard().stopTimer();
		this.buyClockItemLayer.setVisible(true);
	}

	public void hideBuyClockItemLayer()
	{
		enableTouch();
		this.gameBGLayer.getBoard().startTimer();
		this.buyClockItemLayer.setVisible(false);
	}

	public void pauseGame()
	{
		disableTouch();
		this.gameBGLayer.getBoard().stopTimer();
		this.gamePauseLayer.setVisible(true);
	}

	public void resumeGame()
	{
		enableTouch();
		this.gameBGLayer.getBoard().startTimer();
		this.gamePauseLayer.setVisible(false);
	}

	public void updateCoins(int coins)
	{
		this.buyClockItemLayer.updateCoins(coins);
		this.buyFindItemLayer.updateCoins(coins);
	}

	private void enableTouch()
	{
		this.gameLayer.setTouchEnabled(true);
		this.gameBGLayer.getBoard().setTouchEnabled(true);
	}

	private void disableTouch()
	{
		this.gameLayer.setTouchEnabled(false);
		this.gameBGLayer.getBoard().setTouchEnabled(false);
	}

	@Override
	public boolean wyKeyDown(KeyEvent event)
	{
		if (event.getKeyCode() == KeyEvent.KEYCODE_BACK)
		{
			// 道具界面或者游戏结束界面存在时，不显示游戏暂停界面，back键的操作改成关闭上述界面
			if (this.gameOverLayer.isVisible())
			{				
				GameUtil.switchScene(StartScene.make());
			}
			else if (this.buyClockItemLayer.isVisible())
			{				
				this.hideBuyClockItemLayer();
			}
			else if (this.buyFindItemLayer.isVisible())
			{
				this.hideBuyFindItemLayer();
			}
			else if (this.gamePauseLayer.isVisible())
			{
				this.resumeGame();
			}
			else
			{
				this.pauseGame();
			}
			return true;
		}
		return super.wyKeyDown(event);
	}
}
