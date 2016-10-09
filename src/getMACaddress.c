
#include <stdio.h>
#include <stdlib.h>
#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/IOKitLib.h>
#include <IOKit/network/IOEthernetInterface.h>
#include <IOKit/network/IONetworkInterface.h>
#include <IOKit/network/IOEthernetController.h>

static kern_return_t GetMACAddress(io_iterator_t intfIterator, UInt8 *MACAddress, UInt8 bufferSize);

void Trim(char *ptr)
{
    char *p,*q;
    if(ptr==NULL)
        return;
    for(p=ptr; *p==' ' || *p=='\t'|| *p=='\n' ; ++p);
    if( *p==0 )
    {
        *ptr=0;
        return;
    }
    for(q=ptr; *p; ++p,++q)
    {
        *q=*p;
    }
    for(p=q-1; *p==' '||*p=='\t'||*p=='\n'; --p);
    *(++p)='\0';
}

//此函数用来获取用户制定网卡的 Mac Address
void GetMacFromDevice(uint8_t mac[6], const char *devicename)
{
    UInt8 MACAddress[kIOEthernetAddressSize];
    FILE *fp;
    char path[100];
    char query[200];
    const char *d = ":";
    char *p;
    long tp;
    int counter=0;

    /***利用networksetup工具来获取Mac Address****/
    strcat(query, "networksetup -listallhardwareports|grep -A 1 ");
    strcat(query, devicename);
    strcat(query,"|grep 'Ethernet Address'|cut -d ' ' -f 3");
    fp = popen(query, "r");
    if (fp == NULL) {
        printf("Failed to get MacAddress\n" );
        exit(1);
    }
    if (fgets(path, sizeof(path)-1, fp) != NULL) {
        pclose(fp);
    }
    
    Trim(path);
    fclose(fp);
    
    p = strtok(path,d);
    while(p)
    {
        tp=strtol( p, NULL, 16 );
        MACAddress[counter]=tp;
        counter++;
        p=strtok(NULL,d);
    }
    /******************************************/
	printf("This %s's MAC address is %02x:%02x:%02x:%02x:%02x:%02x.\n",devicename,MACAddress[0], MACAddress[1], MACAddress[2], MACAddress[3], MACAddress[4], MACAddress[5]);
    memcpy(mac, MACAddress, 6);

}
