using UnityEngine;
using System;
using System.Collections;
using System.Runtime.InteropServices;
using System.Net;
using System.Threading;

public class NatNetClient : MonoBehaviour {

	public string serverIP;
	public string localIP;
	public IntPtr self;
	Thread workerThread;
	
	static UInt32 IPStringToInt(string ip)
	{
		byte[] bytes = IPAddress.Parse(ip).GetAddressBytes();
		UInt32 res = 0;
		int i;
		for (i = 0; i < 4; i++)
		{
			res += (uint)(bytes[i] << (8*(4 - i - 1)));
		}
		return res;
	}
	
	// Use this for initialization
	void Start () {
		UInt32 addr = IPStringToInt(localIP);
		Debug.Log("Local endpoint:" + addr.ToString());
		self = natnetclient_init(addr);
		
		addr = IPStringToInt(serverIP);
		Debug.Log("Remote endpoint: " + addr.ToString());
		if (addr != 0)
		{
			natnetclient_ping(self, addr);
		}
		workerThread = new Thread(new ThreadStart(ProcessThread));
		workerThread.Start();
	}
			
	void ProcessThread() {
		while (true)
		{
			natnetclient_process_frame(self);
		}
	}
		
	void Destroy () {
		workerThread.Abort();
		natnetclient_destroy(self);
	}
	
	
	[DllImport("optitrack-depack", CallingConvention=CallingConvention.Cdecl)]
	static extern IntPtr natnetclient_init(UInt32 addr);
	[DllImport("optitrack-depack", CallingConvention=CallingConvention.Cdecl)]
	static extern void natnetclient_destroy(IntPtr self);
	[DllImport("optitrack-depack", CallingConvention=CallingConvention.Cdecl)]
	static extern void natnetclient_ping(IntPtr self, UInt32 host);
	[DllImport("optitrack-depack", CallingConvention=CallingConvention.Cdecl)]
	static extern void natnetclient_process_frame(IntPtr self);
}
