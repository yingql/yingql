package com.yingql.android.games.zhaocha.layer;

import com.wiyun.engine.nodes.Button;
import com.wiyun.engine.nodes.Layer;
import com.wiyun.engine.nodes.Sprite;
import com.wiyun.engine.opengl.Texture2D;
import com.wiyun.engine.types.WYPoint;
import com.wiyun.engine.utils.ResolutionIndependent;
import com.wiyun.game.WiGame;
import com.yingql.android.games.zhaocha.MainActivity;
import com.yingql.android.games.zhaocha.R;
import com.yingql.android.games.zhaocha.core.GameSystem;
import com.yingql.android.games.zhaocha.entity.GameMode;
import com.yingql.android.games.zhaocha.entity.UserInfo;
import com.yingql.android.games.zhaocha.scene.GameScene;
import com.yingql.android.games.zhaocha.scene.StartScene;
import com.yingql.android.games.zhaocha.util.GameUtil;
import com.yingql.android.games.zhaocha.util.WiGameUtil;
import com.yingql.android.games.zhaocha.util.db.DatabaseOperator;

public class StartMenuLayer extends Layer
{
	private static final int BG_ZINDEX = 1;
	private static final int BUTTON_ZINDEX = 3;
	private static final int OTHER_ZINDEX = 2;
	private static final int RIGHT_MARGION = 10;
	private static final int TOP_MARGION = 20;
	private static final int SPAN = 40;
	private Button btnSoundOn, btnSoundOff;
	private boolean isWiGameInit = false;

	public StartMenuLayer()
	{
		Sprite bg = Sprite.make(Texture2D.makeJPG(R.drawable.start_scene_bg));
		this.addChild(bg, BG_ZINDEX);
		bg.setPosition(GameSystem.Screen_Width / 2, GameSystem.Screen_Height / 2);
		bg.setScale(GameSystem.Screen_Width / bg.getWidth(), GameSystem.Screen_Height / bg.getHeight());
		bg.autoRelease();

		Sprite image = Sprite.make(Texture2D.makePNG(R.drawable.start_scene_image));
		this.addChild(image, OTHER_ZINDEX);
		image.setAnchorPercent(0, 1);
		image.setPosition(0, GameSystem.Screen_Height);
		image.autoRelease();

		Sprite fangdajing = Sprite.make(Texture2D.makePNG(R.drawable.fangdajing));
		this.addChild(fangdajing, OTHER_ZINDEX);
		fangdajing.setAnchorPercent(0, 0);
		fangdajing.setPosition(ResolutionIndependent.resolve(WYPoint.make(160, -20)));
		fangdajing.autoRelease();

		Sprite title = Sprite.make(Texture2D.makePNG(R.drawable.title));
		this.addChild(title, OTHER_ZINDEX);
		title.setAnchorPercent(0, 0);
		title.setPosition(ResolutionIndependent.resolve(WYPoint.make(14, 20)));
		title.autoRelease();

		float top = TOP_MARGION;

		Button btnQuickGame = Button.make(R.drawable.btn_quickgame_normal, R.drawable.btn_quickgame_active, this, "quickGame");
		this.addChild(btnQuickGame, BUTTON_ZINDEX);
		btnQuickGame.setAnchorPercent(1, 1);
		btnQuickGame.setPosition(GameSystem.Screen_Width - ResolutionIndependent.resolveDp(RIGHT_MARGION), GameSystem.Screen_Height
				- ResolutionIndependent.resolveDp(top));
		btnQuickGame.autoRelease();

		top += SPAN;

		Button btnTimelessGame = Button.make(R.drawable.btn_timeless_game_normal, R.drawable.btn_timelessgame_active, this, "timelessGame");
		this.addChild(btnTimelessGame, BUTTON_ZINDEX);
		btnTimelessGame.setAnchorPercent(1, 1);
		btnTimelessGame.setPosition(GameSystem.Screen_Width - ResolutionIndependent.resolveDp(RIGHT_MARGION), GameSystem.Screen_Height
				- ResolutionIndependent.resolveDp(top));
		btnTimelessGame.autoRelease();

		// top += SPAN;
		//
		// Button btnMutilPlayer =
		// Button.make(R.drawable.btn_mutilplayer_normal,
		// R.drawable.btn_mutilplayer_active, this, "mutilPlayer");
		// this.addChild(btnMutilPlayer, BUTTON_ZINDEX);
		// btnMutilPlayer.setAnchorPercent(1, 1);
		// btnMutilPlayer.setPosition(GameSystem.Screen_Width -
		// ResolutionIndependent.resolveDp(RIGHT_MARGION),
		// GameSystem.Screen_Height
		// - ResolutionIndependent.resolveDp(top));
		// btnMutilPlayer.autoRelease();

		top += SPAN;

		Button btnLeadship = Button.make(R.drawable.btn_leadship_normal, R.drawable.btn_leadship_active, this, "leadship");
		this.addChild(btnLeadship, BUTTON_ZINDEX);
		btnLeadship.setAnchorPercent(1, 1);
		btnLeadship.setPosition(GameSystem.Screen_Width - ResolutionIndependent.resolveDp(RIGHT_MARGION), GameSystem.Screen_Height
				- ResolutionIndependent.resolveDp(top));
		btnLeadship.autoRelease();

		top += SPAN;

		Button btnAchievement = Button.make(R.drawable.btn_achievement_normal, R.drawable.btn_achievement_active, this, "achievement");
		this.addChild(btnAchievement, BUTTON_ZINDEX);
		btnAchievement.setAnchorPercent(1, 1);
		btnAchievement.setPosition(GameSystem.Screen_Width - ResolutionIndependent.resolveDp(RIGHT_MARGION), GameSystem.Screen_Height
				- ResolutionIndependent.resolveDp(top));
		btnAchievement.autoRelease();

		top += SPAN;

		Button btnHelp = Button.make(R.drawable.btn_help_normal, R.drawable.btn_help_active, this, "showHelp");
		this.addChild(btnHelp, BUTTON_ZINDEX);
		btnHelp.setAnchorPercent(1, 1);
		btnHelp.setPosition(GameSystem.Screen_Width - ResolutionIndependent.resolveDp(RIGHT_MARGION), GameSystem.Screen_Height
				- ResolutionIndependent.resolveDp(top));
		btnHelp.autoRelease();

		// 根据用户设置按钮的可见性
		boolean isMusicOn = DatabaseOperator.getUserInfo().isMusicOn();

		btnSoundOn = Button.make(R.drawable.sound_on, 0, this, "setMusic");
		this.addChild(btnSoundOn, BUTTON_ZINDEX);
		btnSoundOn.setAnchorPercent(1, 0);
		btnSoundOn.setPosition(GameSystem.Screen_Width - ResolutionIndependent.resolveDp(RIGHT_MARGION), ResolutionIndependent.resolveDp(10));
		btnSoundOn.autoRelease();
		btnSoundOn.setVisible(isMusicOn);

		btnSoundOff = Button.make(R.drawable.sound_off, 0, this, "setMusic");
		this.addChild(btnSoundOff, BUTTON_ZINDEX);
		btnSoundOff.setAnchorPercent(1, 0);
		btnSoundOff.setPosition(GameSystem.Screen_Width - ResolutionIndependent.resolveDp(RIGHT_MARGION), ResolutionIndependent.resolveDp(10));
		btnSoundOff.autoRelease();
		btnSoundOff.setVisible(!isMusicOn);

		this.setTouchEnabled(true);
	}

	public void init()
	{
		GameSystem.playBGMusic();
		if (!isWiGameInit)
		{
			isWiGameInit = true;
			WiGameUtil.init(MainActivity.Instance);
		}
	}

	public void quickGame()
	{
		if (this.isTouchEnabled())
		{
			if (!GameSystem.loadGameProgress(GameMode.QuickGame))
			{
				GameUtil.switchScene(GameScene.make());
				GameSystem.initQuickGame();
			}
		}
	}

	public void timelessGame()
	{
		if (this.isTouchEnabled())
		{
			if (!GameSystem.loadGameProgress(GameMode.Timeless))
			{
				GameUtil.switchScene(GameScene.make());
				GameSystem.initTimelessGame();
			}
		}
	}

	public void leadship()
	{
		if (this.isTouchEnabled())
		{
			WiGame.openLeaderboards();
		}
	}

	public void achievement()
	{
		if (this.isTouchEnabled())
		{
			WiGame.openAchievements();
		}
	}

	public void showHelp()
	{
		if (this.isTouchEnabled())
		{
			StartScene.getInstance().showHelp();
		}
	}

	public void setMusic()
	{
		if (this.isTouchEnabled())
		{
			UserInfo userInfo = DatabaseOperator.getUserInfo();
			boolean isMusicOn = !userInfo.isMusicOn();
			userInfo.setMusicOn(isMusicOn);
			DatabaseOperator.saveUserInfo(userInfo);
			if (isMusicOn)
				GameSystem.playBGMusic();
			else
				GameSystem.stopBGMusic();
			btnSoundOn.setVisible(isMusicOn);
			btnSoundOff.setVisible(!isMusicOn);
		}
	}
}
