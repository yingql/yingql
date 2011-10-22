package com.yingql.android.games.zhaocha.util.db;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteDatabase.CursorFactory;
import android.database.sqlite.SQLiteOpenHelper;

import com.yingql.android.games.zhaocha.entity.UserInfo;

public class DatabaseHelper extends SQLiteOpenHelper
{
	private static final int VERSION = 1;

	public DatabaseHelper(Context context, String name, CursorFactory factory, int version)
	{
		super(context, name, factory, version);
	}

	public DatabaseHelper(Context context, String name, int version)
	{
		this(context, name, null, version);
	}

	public DatabaseHelper(Context context, String name)
	{
		this(context, name, VERSION);
	}

	@Override
	public void onCreate(SQLiteDatabase db)
	{
		System.out.println("Create a database.");
		// 创建初始数据
		initDB(db);
	}

	/**
	 * 初始化数据库
	 */
	public static void initDB(SQLiteDatabase db)
	{
		db.execSQL(DataBaseMetaData.UserInfoTableMetaData.getCreateSql());		
		UserInfo userInfo = new UserInfo();
		// 设置用户初始数据
		userInfo.setCoins(500);
		userInfo.setClockItemCount(10);
		userInfo.setFindItemCount(10);
		
		DatabaseOperator.saveUserInfo(db, userInfo);		
	}

	@Override
	public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion)
	{
		// TODO 后期的升级需要保存原来的数据，保证无缝升级，现在直接删除旧数据
		System.out.println("onUpgrade.");
		// 删除原有数据
		db.execSQL("drop table " + DataBaseMetaData.USERINFO_TABLE_NAME);
		// 创建初始数据
		initDB(db);
	}
}
