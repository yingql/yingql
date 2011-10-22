package com.yingql.android.games.zhaocha.layer;

import com.wiyun.engine.nodes.Button;
import com.wiyun.engine.nodes.Label;
import com.wiyun.engine.nodes.Layer;
import com.wiyun.engine.nodes.Sprite;
import com.wiyun.engine.types.WYPoint;
import com.wiyun.engine.utils.ResolutionIndependent;
import com.yingql.android.games.zhaocha.R;
import com.yingql.android.games.zhaocha.core.GameStrategy;
import com.yingql.android.games.zhaocha.core.GameSystem;
import com.yingql.android.games.zhaocha.entity.GameInfo;
import com.yingql.android.games.zhaocha.scene.StartScene;
import com.yingql.android.games.zhaocha.util.GameUtil;

public class GameOverLayer extends Layer
{
	private Label lbScore, lbHiScore, lbMaxCombo, lbRate;
	private Sprite[] stars;

	public GameOverLayer()
	{
		stars = new Sprite[3];

		float cx = GameSystem.Screen_Width / 2, cy = GameSystem.Screen_Height / 2;

		Sprite mask = Sprite.make(R.drawable.mask);
		mask.setPosition(WYPoint.make(cx, cy));
		mask.setScale(GameSystem.Screen_Width / mask.getWidth(), GameSystem.Screen_Height / mask.getHeight());
		this.addChild(mask, 0);
		mask.autoRelease();

		Sprite bg = Sprite.make(R.drawable.gameoverbg);
		bg.setDither(true);
		bg.setPosition(WYPoint.make(cx, cy));
		this.addChild(bg, 1);
		bg.autoRelease();

		float lbX = cx + ResolutionIndependent.resolveDp(10);
		float lbY = cy + ResolutionIndependent.resolveDp(77);
		float span = ResolutionIndependent.resolveDp(28);

		lbScore = Label.make("0", 18);
		lbScore.setAnchorPercent(0, 1);
		lbScore.setPosition(WYPoint.make(lbX, lbY));
		this.addChild(lbScore, 2);
		lbScore.autoRelease();

		lbY -= span;

		lbHiScore = Label.make("0", 18);
		lbHiScore.setAnchorPercent(0, 1);
		lbHiScore.setPosition(WYPoint.make(lbX, lbY));
		this.addChild(lbHiScore, 2);
		lbHiScore.autoRelease();

		lbY -= span;

		lbMaxCombo = Label.make("0", 18);
		lbMaxCombo.setAnchorPercent(0, 1);
		lbMaxCombo.setPosition(WYPoint.make(lbX, lbY));
		this.addChild(lbMaxCombo, 2);
		lbMaxCombo.autoRelease();

		lbY -= span;

		lbRate = Label.make("0", 18);
		lbRate.setAnchorPercent(0, 1);
		lbRate.setPosition(WYPoint.make(lbX, lbY));
		this.addChild(lbRate, 2);
		lbRate.autoRelease();

		Button btnMenu = Button.make(R.drawable.btn_menu_normal, R.drawable.btn_menu_active, this, "backToMenu");
		btnMenu.setAnchorPercent(1, 0);
		btnMenu.setPosition(WYPoint.make(cx - ResolutionIndependent.resolveDp(5), cy - ResolutionIndependent.resolveDp(122)));
		this.addChild(btnMenu, 2);
		btnMenu.autoRelease();

		Button btnRetry = Button.make(R.drawable.btn_retry_normal, R.drawable.btn_retry_active, this, "retry");
		btnRetry.setAnchorPercent(0, 0);
		btnRetry.setPosition(WYPoint.make(cx + ResolutionIndependent.resolveDp(5), cy - ResolutionIndependent.resolveDp(122)));
		this.addChild(btnRetry, 2);
		btnRetry.autoRelease();
	}

	public void backToMenu()
	{
		GameUtil.switchScene(StartScene.getInstance());
	}

	public void retry()
	{
		GameSystem.retry();
	}

	public void init()
	{
		GameInfo info = GameSystem.getGameInfo();
		lbScore.setText(info.getCurScore() + "");
		lbHiScore.setText(info.getHighScore() + "");
		lbMaxCombo.setText(info.getMaxCombo() + "");
		float rate = (float) info.getRightCount() / info.getClickCount() * 100.0f;
		lbRate.setText(String.format("%1$.2f", rate) + "%");
		int rank = GameStrategy.calcRanks(info.getCurScore(), info.getMaxCombo(), rate, info.getMode());

		for (int i = 0; i < 3; i++)
		{
			if (stars[i] != null)
				this.removeChild(stars[i], true);
		}

		int index = 0;
		while (index < 3)
		{
			if (rank >= 4)
			{
				stars[index] = getStar(4);
				rank -= 4;
			}
			else
			{
				stars[index] = getStar(rank);
				rank = 0;
			}
			index++;
		}

		float cx = GameSystem.Screen_Width / 2, cy = GameSystem.Screen_Height / 2;

		for (int i = 0; i < 3; i++)
		{
			stars[i].setAnchorPercent(0, 0.5f);
			stars[i].setPosition(WYPoint.make(cx + ResolutionIndependent.resolveDp(8 + 27 * i), cy - ResolutionIndependent.resolveDp(58)));
			this.addChild(stars[i], 2);
			stars[i].autoRelease();
		}
	}

	private Sprite getStar(int rank)
	{
		return Sprite.make(GameUtil.getResId("star_" + rank));
	}
}
