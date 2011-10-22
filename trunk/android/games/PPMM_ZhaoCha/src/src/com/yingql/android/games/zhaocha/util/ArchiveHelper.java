package com.yingql.android.games.zhaocha.util;

import java.util.ArrayList;
import java.util.List;

import android.content.SharedPreferences;

import com.yingql.android.games.zhaocha.MainActivity;
import com.yingql.android.games.zhaocha.entity.Archive;
import com.yingql.android.games.zhaocha.entity.GameMode;

/**
 * 存档帮助类
 * 
 * @author yingql
 * 
 */
public class ArchiveHelper
{
	private static final String PREFS_NAME = "Archive";
	private static final String HAS_QUICK_GAME_ARCHIVE = "hasQuickGameArchive";
	private static final String HAS_TIMELESS_GAME_ARCHIVE = "hasTimelessGameArchive";

	private static final String MODE_QUICK_GAME = "quickGame_";
	private static final String MODE_TIMELESS_GAME = "timeless_";

	private static final String REMAIN_TIME = "remainTime";
	private static final String SCORE = "score";
	private static final String CURCOMBO = "curCombo";
	private static final String MAXCOMBO = "maxCombo";
	private static final String CLICK_COUNT = "clickCount";
	private static final String RIGHT_COUNT = "rightCount";
	private static final String LEVEL_COUNT = "levelCount";
	private static final String MAP_INDEX = "mapIndex";
	private static final String PIECES_PATH = "piecesPath";
	private static final String FOUND_PIECES_PATH = "foundPiecesPath";

	/**
	 * 获取指定的游戏模式是否有存档
	 * 
	 * @param mode
	 * @return
	 */
	public static boolean hasArchive(GameMode mode)
	{
		SharedPreferences settings = MainActivity.Instance.getSharedPreferences(PREFS_NAME, 0);
		String key = HAS_QUICK_GAME_ARCHIVE;
		switch (mode)
		{
			case QuickGame:
				key = HAS_QUICK_GAME_ARCHIVE;
				break;
			case Timeless:
				key = HAS_TIMELESS_GAME_ARCHIVE;
				break;
		}
		return settings.getBoolean(key, false);
	}

	/**
	 * 设置指定模式是否存在的存档
	 * 
	 * @param mode
	 */
	public static void setHasArchive(GameMode mode, boolean hasArchive)
	{
		SharedPreferences settings = MainActivity.Instance.getSharedPreferences(PREFS_NAME, 0);
		SharedPreferences.Editor editor = settings.edit();
		String key = HAS_QUICK_GAME_ARCHIVE;
		switch (mode)
		{
			case QuickGame:
				key = HAS_QUICK_GAME_ARCHIVE;
				break;
			case Timeless:
				key = HAS_TIMELESS_GAME_ARCHIVE;
				break;
		}
		editor.putBoolean(key, hasArchive);
		editor.commit();
	}

	private static Archive getArchive(String mode)
	{
		Archive archive = new Archive();
		SharedPreferences settings = MainActivity.Instance.getSharedPreferences(PREFS_NAME, 0);
		archive.setRemainTime(settings.getFloat(mode + REMAIN_TIME, 0));
		archive.setScore(settings.getInt(mode + SCORE, 0));
		archive.setCurCombo(settings.getInt(mode + CURCOMBO, 0));
		archive.setMaxCombo(settings.getInt(mode + MAXCOMBO, 0));
		archive.setLevelCount(settings.getInt(mode + LEVEL_COUNT, 0));
		archive.setMapIndex(settings.getInt(mode + MAP_INDEX, 1));
		archive.setClickCount(settings.getInt(mode + CLICK_COUNT, 0));
		archive.setRightCount(settings.getInt(mode + RIGHT_COUNT, 0));
		String[] pieces = settings.getString(mode + PIECES_PATH, "").split(Archive.SPLIT_CHAR);
		List<Integer> temp = new ArrayList<Integer>();
		for (int i = 0; i < pieces.length; i++)
		{
			temp.add(Integer.parseInt(pieces[i]));
		}
		archive.setPieces(temp);
		String t = settings.getString(mode + FOUND_PIECES_PATH, "");
		String[] foundPieces = t.split(Archive.SPLIT_CHAR);
		List<Integer> temp2 = new ArrayList<Integer>();
		if (t != null && t.length() > 0)
		{
			for (int i = 0; i < foundPieces.length; i++)
			{
				temp2.add(Integer.parseInt(foundPieces[i]));
			}
		}
		archive.setFoundPieces(temp2);
		return archive;
	}

	private static void saveArchive(String mode, Archive archive)
	{
		SharedPreferences settings = MainActivity.Instance.getSharedPreferences(PREFS_NAME, 0);
		SharedPreferences.Editor editor = settings.edit();
		editor.putFloat(mode + REMAIN_TIME, archive.getRemainTime());
		editor.putInt(mode + SCORE, archive.getScore());
		editor.putInt(mode + CURCOMBO, archive.getCurCombo());
		editor.putInt(mode + MAXCOMBO, archive.getMaxCombo());
		editor.putInt(mode + LEVEL_COUNT, archive.getLevelCount());
		editor.putInt(mode + MAP_INDEX, archive.getMapIndex());
		editor.putInt(mode + CLICK_COUNT, archive.getClickCount());
		editor.putInt(mode + RIGHT_COUNT, archive.getRightCount());
		String pieces = "";
		for (Integer piece : archive.getPieces())
		{
			pieces += piece + Archive.SPLIT_CHAR;
		}
		if (pieces.length() > 0)
			pieces = pieces.substring(0, pieces.length() - 1);
		editor.putString(mode + PIECES_PATH, pieces);

		String foundPieces = "";
		for (Integer piece : archive.getFoundPieces())
		{
			foundPieces += piece + Archive.SPLIT_CHAR;
		}
		if (foundPieces.length() > 0)
			foundPieces = foundPieces.substring(0, foundPieces.length() - 1);
		editor.putString(mode + FOUND_PIECES_PATH, foundPieces);
		editor.commit();
	}

	public static Archive getQuickGameArchive()
	{
		return getArchive(MODE_QUICK_GAME);
	}

	public static void saveQuickGameArchive(Archive archive)
	{
		saveArchive(MODE_QUICK_GAME, archive);
	}

	public static Archive getTimelessArchive()
	{
		return getArchive(MODE_TIMELESS_GAME);
	}

	public static void saveTimelessArchive(Archive archive)
	{
		saveArchive(MODE_TIMELESS_GAME, archive);
	}
}
