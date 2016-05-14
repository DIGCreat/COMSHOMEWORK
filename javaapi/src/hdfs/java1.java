package hdfs;

import java.io.InputStream;
import java.io.IOException;
import java.net.URL;

import org.apache.hadoop.fs.FsUrlStreamHandlerFactory;
import org.apache.hadoop.io.IOUtils;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FSDataOutputStream;
import org.apache.hadoop.fs.FileStatus;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;

public class java1 {
	static final String PATH = "hdfs://localhost:9000/URL";
	
	//initialization
	static Configuration conf = new Configuration();
	static FileSystem fs;
	static {
		String path = "/opt/hadoop-1.2.1/conf/";
		conf.addResource(new Path(path + "core-site.xml"));
		conf.addResource(new Path(path + "hdfs-site.xml"));
		conf.addResource(new Path(path + "mapred-site.xml"));
		try {
			fs = FileSystem.get(conf);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public static void main(String[] args) throws Exception {
		URL.setURLStreamHandlerFactory(new FsUrlStreamHandlerFactory());
		
		final URL url = new URL(PATH);
		final InputStream in = url.openStream();
		Path dirpath = new Path("/testdir");
		Path rootpath = new Path("/");
		Path srcPath = new Path("/home/king/somedata.txt");
		Path urlPath = new Path("/URL");
		
		//获取文件系统的根目录下的文件
		FileStatus[] status = fs.listStatus(rootpath);
		System.out.println("根目录下当前的所以文件及目录：");
		for (int i = 0; i< status.length; i++) {
			System.out.println(status[i].getPath().toString());
		}
		
		//新建目录“testdir”
		fs.mkdirs(dirpath);
		
		//删除目录“mydir”
		dirpath = new Path("/mydir");
		fs.delete(dirpath);
		
		//上传文件
		fs.copyFromLocalFile(srcPath, rootpath);
		
		//下载文件
		srcPath = new Path("/home/king/");
		fs.copyToLocalFile(urlPath, srcPath);
		
		//获取文件系统的根目录下的文件
		status = fs.listStatus(rootpath);
		System.out.println("根目录下当前的所以文件及目录：");
		for (int i = 0; i< status.length; i++) {
			System.out.println(status[i].getPath().toString());
		}
		System.out.println("读取/URL的文件内容：");
		IOUtils.copyBytes(in, System.out, 1024, true);
		fs.close();

	}
}

