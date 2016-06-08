package hbaseproject;

import java.io.IOException;
import org.apache.hadoop.conf.*;
import org.apache.hadoop.hbase.*;
import org.apache.hadoop.hbase.client.*;
import org.apache.hadoop.hbase.util.Bytes;

public class Hbasetest {
	// 声明静态配置
    static Configuration conf = null;
    static {
        conf = HBaseConfiguration.create();
        conf.set("hbase.zookeeper.quorum", "localhost");
    }

	public static void createTable(String tableName, String[] columnFamily) throws IOException{
		HBaseAdmin admin = new HBaseAdmin(conf);
		if (admin.tableExists(tableName)) {
			System.out.println("table exists!");
			delete(tableName);
		}
		HTableDescriptor tableDesc = new HTableDescriptor(tableName);
		for (int i = 0; i < columnFamily.length; i++) {
	        tableDesc.addFamily(new HColumnDescriptor(columnFamily[i]));
	    }
		admin.createTable(tableDesc);
		System.out.println("create table success!");
		
	}

	//添加一条记录
	public static void addRecord(String tableName, String row, String columnFamily, String[] columns, String[] datas) throws IOException{
		HTable table = new HTable(conf, tableName);
		Put p1 = new Put(Bytes.toBytes(row));
		for(int i = 0; i < columns.length; i++){
			p1.add(Bytes.toBytes(columnFamily), Bytes.toBytes(columns[i]), 	Bytes.toBytes(datas[i]));
		    table.put(p1);
		    System.out.println("put'"+row+"',"+columnFamily+":"+columns[i]+"','"+datas[i]+"'");
		}
	}

	//读取一条记录
	public static void get(String tableName, String row) throws IOException{
		HTable table = new HTable(conf, tableName);
		Get get = new Get(Bytes.toBytes(row));
		Result result = table.get(get);
		System.out.println("Get: "+result);
	}

	 /*
     * 查询表中的某一列
     * 
     * @tableName 表名
     * 
     * @rowKey rowKey
     */
    public static void scanColumn(String tableName, String rowKey,
            String familyName, String columnName) throws IOException {
        HTable table = new HTable(conf, Bytes.toBytes(tableName));
        Get get = new Get(Bytes.toBytes(rowKey));
        get.addColumn(Bytes.toBytes(familyName), Bytes.toBytes(columnName)); // 获取指定列族和列修饰符对应的列
        Result result = table.get(get);
        for (KeyValue kv : result.list()) {
            System.out.println("family:" + Bytes.toString(kv.getFamily()));
            System.out
                    .println("qualifier:" + Bytes.toString(kv.getQualifier()));
            System.out.println("value:" + Bytes.toString(kv.getValue()));
            System.out.println("Timestamp:" + kv.getTimestamp());
            System.out.println("-------------------------------------------");
        }
    }

	//显示所有数据
	public static void scan(String tableName) throws IOException{
		HTable table = new HTable(conf, tableName);
		Scan scan = new Scan();
		ResultScanner scanner = table.getScanner(scan);
		for (Result result : scanner) {
			System.out.println("Scan: "+result);
		}
	}

	/*
     * 删除指定的列
     * 
     * @tableName 表名
     * 
     * @rowKey rowKey
     */
    public static void deleteAllColumn(String tableName, String rowKey)
            throws IOException {
        HTable table = new HTable(conf, Bytes.toBytes(tableName));
        Delete deleteAll = new Delete(Bytes.toBytes(rowKey));
        table.delete(deleteAll);
        System.out.println("all columns are deleted!");
    }

	//删除表
	public static void delete(String tableName) throws IOException{
		HBaseAdmin admin = new HBaseAdmin(conf);
		if(admin.tableExists(tableName)){
			try {
			  admin.disableTable(tableName);
			  admin.deleteTable(tableName);
			} catch (IOException e) {
			  e.printStackTrace();
			  System.out.println("Delete "+tableName+" 失败");
			}
		}
		System.out.println("Delete "+tableName+" 成功");
	}
	
	public static void main(String[] args) throws Exception{
		String[] tableNames = {"Student", "Course", "SC"};
		String[] family = {"property"};
		String[] S_rowkeys = {"2015001", "2015002", "2015003"};
		String[] S_columns = {"S_Name", "S_Sex", "S_Age"};
		String[][] S_datas = {{"Zhangsan", "male", "23"}, {"Mary", "female", "22"},{"Lisi", "male", "24"}};
		String[] C_rowkeys = {"123001", "123002", "123003"};
		String[] C_columns = {"C_Name", "C_Credit"};
		String[][] C_datas = {{"Math", "2.0"}, {"ComputerScience", "5.0"}, {"English", "3.0"}};
		String[][] SC_Column = {{"123001", "123003"}, {"123002", "123003"}, {"123001", "123002"}};
		String[][] SC_datas = {{"86", "69"}, {"77", "99"}, {"98", "95"}};
		for(int i = 0; i < tableNames.length; i++){
			createTable(tableNames[i], family);
		}
		
		//添加数据
		for(int i = 0; i < S_rowkeys.length; i++){
			addRecord(tableNames[0], S_rowkeys[i], family[0], S_columns, S_datas[i]);
		}
		for(int i = 0; i < S_rowkeys.length; i++){
			addRecord(tableNames[1], C_rowkeys[i], family[0], C_columns, C_datas[i]);
		}
		for(int i = 0; i < S_rowkeys.length; i++){
			addRecord(tableNames[2], S_rowkeys[i], family[0], SC_Column[i], SC_datas[i]);
		}
	}
}
