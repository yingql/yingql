package com.yingql.android.games.zhaocha.sprite;

import com.wiyun.engine.nodes.AtlasLabel;
import com.wiyun.engine.nodes.Node;
import com.wiyun.engine.nodes.Sprite;
import com.wiyun.engine.opengl.Texture2D;
import com.wiyun.engine.types.WYColor3B;
import com.wiyun.engine.utils.ResolutionIndependent;
import com.wiyun.engine.utils.TargetSelector;
import com.yingql.android.games.zhaocha.R;
import com.yingql.android.games.zhaocha.core.GameStrategy;
import com.yingql.android.games.zhaocha.core.GameSystem;
import com.yingql.android.games.zhaocha.entity.GameInfo;

public class GameInfoBoard extends Node
{
	private int levelCount = 0;
	private int highScore = 0;
	private int score = 0;
	private int combo = 0;
	private float remainTime = 30;
	private AtlasLabel lbLevel;
	private AtlasLabel lbHiScore;
	private AtlasLabel lbScore;
	private AtlasLabel lbCombo;
	private AtlasLabel lbRemainTime;
	private TargetSelector selector;
	private FindItemButton findItemBtn;
	private ClockItemButton clockItemBtn;

	public GameInfoBoard()
	{
		Texture2D texture = Texture2D.makePNG(R.drawable.numbers);

		// 关卡
		Sprite level = Sprite.make(R.drawable.lb_level);
		// Label level = Label.make("关卡", 20);
		level.setAnchorPercent(0, 1);
		level.setPosition(0, -ResolutionIndependent.resolveDp(2));
		this.addChild(level);
		level.autoRelease();

		lbLevel = AtlasLabel.make("1", texture, GameSystem.WhiteCharMap);
		lbLevel.setAnchorPercent(1, 1);
		lbLevel.setPosition(ResolutionIndependent.resolveDp(76), -ResolutionIndependent.resolveDp(2));
		this.addChild(lbLevel);
		lbLevel.autoRelease();

		// 最高分
		Sprite hiScore = Sprite.make(R.drawable.lb_hiscore);
		// Label hiScore = Label.make("最高分", 20);
		hiScore.setAnchorPercent(0, 1);
		hiScore.setPosition(0, -ResolutionIndependent.resolveDp(27));
		this.addChild(hiScore);
		hiScore.autoRelease();

		lbHiScore = AtlasLabel.make("0", texture, GameSystem.WhiteCharMap);
		lbHiScore.setAnchorPercent(1, 1);
		lbHiScore.setPosition(ResolutionIndependent.resolveDp(76), -ResolutionIndependent.resolveDp(52));
		this.addChild(lbHiScore);
		lbHiScore.autoRelease();

		// 当前得分
		Sprite curScore = Sprite.make(R.drawable.lb_score);
		// Label curScore = Label.make("当前得分", 20);
		curScore.setAnchorPercent(0, 1);
		curScore.setPosition(0, -ResolutionIndependent.resolveDp(77));
		this.addChild(curScore);
		curScore.autoRelease();

		lbScore = AtlasLabel.make("0", texture, GameSystem.WhiteCharMap);
		lbScore.setAnchorPercent(1, 1);
		lbScore.setPosition(ResolutionIndependent.resolveDp(76), -ResolutionIndependent.resolveDp(102));
		this.addChild(lbScore);
		lbScore.autoRelease();

		// 连击
		Sprite combo1 = Sprite.make(R.drawable.lb_combo);
		// Label combo1 = Label.make("连击", 20);
		combo1.setAnchorPercent(0, 1);
		combo1.setPosition(0, -ResolutionIndependent.resolveDp(127));
		this.addChild(combo1);
		combo1.autoRelease();

		lbCombo = AtlasLabel.make("0", texture, GameSystem.RedCharMap);
		lbCombo.setAnchorPercent(1, 1);
		lbCombo.setPosition(ResolutionIndependent.resolveDp(76), -ResolutionIndependent.resolveDp(129));
		this.addChild(lbCombo);
		lbCombo.autoRelease();

		// 剩余时间
		Sprite remainTime1 = Sprite.make(R.drawable.lb_remaintime);
		// Label remainTime1 = Label.make("剩余时间", 20);
		remainTime1.setAnchorPercent(0, 1);
		remainTime1.setPosition(0, -ResolutionIndependent.resolveDp(152));
		this.addChild(remainTime1);
		remainTime1.autoRelease();

		lbRemainTime = AtlasLabel.make("0", texture, GameSystem.WhiteCharMap);
		lbRemainTime.setAnchorPercent(1, 1);
		lbRemainTime.setPosition(ResolutionIndependent.resolveDp(76), -ResolutionIndependent.resolveDp(177));
		this.addChild(lbRemainTime);
		lbRemainTime.autoRelease();

		selector = new TargetSelector(this, "tick(float)", new Object[] { 0f });

		findItemBtn = new FindItemButton(this);
		findItemBtn.setAnchorPercent(0, 1);
		findItemBtn.setPosition(0, -ResolutionIndependent.resolveDp(230));
		this.addChild(findItemBtn);
		findItemBtn.autoRelease();

		clockItemBtn = new ClockItemButton(this);
		clockItemBtn.setAnchorPercent(0, 1);
		clockItemBtn.setPosition(0, -ResolutionIndependent.resolveDp(265));
		this.addChild(clockItemBtn);
		clockItemBtn.autoRelease();
	}

	public int getLevelCount()
	{
		return levelCount;
	}

	public void setLevelCount(int levelCount)
	{
		this.levelCount = levelCount;
		if (lbLevel != null)
		{
			lbLevel.setText((this.levelCount + 1) + "");
		}
	}

	public int getHighScore()
	{
		return highScore;
	}

	public void setHighScore(int highScore)
	{
		this.highScore = highScore;
		if (lbHiScore != null)
		{
			lbHiScore.setText(this.highScore + "");
		}
	}

	public int getScore()
	{
		return score;
	}

	public void setScore(int score)
	{
		this.score = score;
		if (lbScore != null)
		{
			lbScore.setText(this.score + "");
		}
	}

	public int getCombo()
	{
		return combo;
	}

	public void setCombo(int combo)
	{
		this.combo = combo;
		if (lbCombo != null)
		{
			lbCombo.setText(this.combo + "");
		}
	}

	public float getRemainTime()
	{
		return remainTime;
	}

	private float timeSpan = 0f;
	private boolean isPlaying = false;

	public void setRemainTime(float remainTime)
	{
		timeSpan += this.remainTime - remainTime;
		this.remainTime = remainTime;
		if (lbRemainTime != null)
		{
			lbRemainTime.setText(String.format("%.1f", this.remainTime));
		}
		// 时间不足，颜色变成红色，并且播放alarm
		if (this.remainTime <= GameStrategy.ALARM_TIME)
		{
			lbRemainTime.setColor(WYColor3B.make(255, 0, 0));
			if (!isPlaying)
			{
				isPlaying = true;
				GameSystem.playEffect(R.raw.alarm);
			}
			else if (timeSpan >= 2f)
			{
				timeSpan = 0f;
				GameSystem.playEffect(R.raw.alarm);
			}
		}
		else
		{
			isPlaying = false;
			timeSpan = 0f;
			lbRemainTime.setColor(WYColor3B.make(255, 255, 255));
		}
		if (this.remainTime <= 0)
		{
			stopTimer();
			// 游戏结束
			GameSystem.endGame();
		}
	}

	/**
	 * 初始化游戏信息
	 * 
	 * @param info
	 */
	public void init(GameInfo info)
	{
		lbHiScore.setColor(WYColor3B.make(255, 255, 255));
		setHighScore(info.getHighScore());
		setRemainTime(info.getTotalTime());
		findItemBtn.setCount(info.getFindItemCount());
		clockItemBtn.setCount(info.getClockItemCount());
		update(info);
	}

	public void setFindItemCount(int count)
	{
		findItemBtn.setCount(count);
	}

	public void setClockItemCount(int count)
	{
		clockItemBtn.setCount(count);
	}

	/**
	 * 更新游戏信息 暂时为分数、连击和关卡数
	 * 
	 * @param info
	 */
	public void update(GameInfo info)
	{
		setLevelCount(info.getLevelCount());
		setScore(info.getCurScore());
		setCombo(info.getCurCombo());
		if (info.isNewRecord())
		{
			setHighScore(info.getHighScore());
			lbHiScore.setColor(WYColor3B.make(255, 0, 0));
		}
	}

	/**
	 * 开启倒计时
	 */
	public void startTimer()
	{
		this.schedule(selector, 0.1f);
	}

	public void stopTimer()
	{
		this.unschedule(this.selector);
	}

	public void tick(float time)
	{
		setRemainTime(Math.max(0, this.remainTime - time));
	}
}
