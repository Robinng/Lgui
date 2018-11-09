/*
	Copyright (C) 2004-2005 Li Yudong
*/
/*
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "../include/common.h"
#include "../include/keyboard_pro.h"
#include "../include/imewin.h"
#include "../include/pinyin.h"



extern ImeDataTable imeDataTable;


typedef struct _CodeTable{
	char* pPinyin;
	char* pHanzi;
} CodeTable;
typedef CodeTable* PCodeTable;

#define MAX_ITEMS	406

CodeTable codeTable[] = {
{"a"			,	"�����������߹"},
{"ai"			,	"�������������������������������������������"},
{"an"		,	"�������������������������ư��������"},
{"ang"		,	"������"},
{"ao"		,	"�°İ���������������������������������������"},
{"ba"		,	"�Ѱ˰ɰͰְհΰȰŰ԰аǰ̰ϰӰʰ����������ᱰ�����"},
{"bai"		,	"�ٰװܰڲ��ݰ�������۰�"},
{"ban"		,	"����������߰���������������"},
{"bang"		,	"�������������亰������"},
{"bao"		,	"���������������������������ٰ��������������������"},
{"bei"		,	"��������������������������㣱��±��������������������ɱ�"},
{"ben"		,	"�����������������"},
{"beng"		,	"���±��ı�괱��԰�"},
{"bi"			,	"�ȱرʱϱұܱձǱ˱Ʊڱ۱ױ̱ɱбα�ذ赱ֱ������㹱��������������޵�����������������Ա����ݩ��������������"},
{"bian"		,	"���߱�����ޱ������������������������������"},
{"biao"		,	"������ڱ�����������������"},
{"bie"		,	"��������"},
{"bin"		,	"���������������ı�������������"},
{"bing"		,	"������������������������"},
{"bo"		,	"�����������������ذ������������������������粤������������뢲�����������"},
{"bu"		,	"����������������������߲�������������"},
{"ca"		,	"������"},
{"cai"		,	"�Ųɲ˲ƲĲʲò²̲Ȳ�"},
{"can"		,	"�βͲвҲӲѲ������������"},
{"cang"		,	"�زԲֲײ���"},
{"cao"		,	"�ݲٲܲ��в������"},
{"ce"		,	"�߲��޲���"},
{"cen"		,	"����"},
{"ceng"		,	"�������"},
{"cha"		,	"������ɲ�����������������������������"},
{"chai"		,	"�������٭���"},
{"chan"		,	"��������������������������Ʋ��������������������"},
{"chang"		,	"�����������������������ȳ���潲���������������������"},
{"chao"		,	"�����������������³���������"},
{"che"		,	"����������������"},
{"chen"		,	"�Ƴ³��������óĳ�����衳���������������"},
{"cheng"		,	"�ɳǳ̳Ƴг�ʢ�˳ʳųͳγ�������ة������������������"},
{"chi"		,	"�Գֳٳ߳��سճݳ۳ܳ�׳�����ള������߳�����������ܯ����������������"},
{"chong"		,	"�س���������������"},
{"chou"		,	"������������㰳����ٱ���"},
{"chu"		,	"�������������������������������ƴ����������ۻ������ء��"},
{"chuai"		,	"�����������"},
{"chuan"		,	"�������������������밴���"},
{"chuang"	,	"��������������"},
{"chui"		,	"��������������"},
{"chun"		,	"������������������ݻ"},
{"chuo"		,	"�´�������"},
{"ci"			,	"�˴δʲ�̴ǴȴŴʹ��ȴĴ�������������"},
{"cong"		,	"�ӴҴϴԴд������������"},
{"cou"		,	"������"},
{"cu"		,	"�ٴִش����������������"},
{"cuan"		,	"�ܴܴ۴�ߥ������"},
{"cui"		,	"���ߴݴ��ʹ�������������"},
{"cun"		,	"��������"},
{"cuo"		,	"�������������������������"},
{"da"		,	"���������������������������"},
{"dai"		,	"���������������������쵡����ʴ�߾���ܤ߰"},
{"dan"		,	"���������������������������壵����������������̵���"},
{"dang"		,	"�����������������������"},
{"dao"		,	"����������������������߶���������"},
{"de"		,	"�ĵõ��"},
{"deng"		,	"�ȵǵƵ˵ʵɵ������������"},
{"di"			,	"�ص���׵͵۵ܵеֵݵεϵٵ̵ѵ޵���ڮ�е�ۡ���յ�����ݶ����������ص�������"},
{"dia"		,	"��"},
{"dian"		,	"�����ߵ��������������ڵ�������������ؼ"},
{"diao"		,	"����������������������"},
{"die"		,	"������������������������ܦ�������"},
{"ding"		,	"������������������������궧���������"},
{"diu"		,	"����"},
{"dong"		,	"�����������������˶���������������"},
{"dou"		,	"����������������������"},
{"du"		,	"�����ȶ������ɶǶŶö¶Ķ������빶ƶ�������ܶ�"},
{"duan"		,	"�϶ζ̶˶Ͷ������"},
{"dui"		,	"�ԶӶѶ���������"},
{"dun"		,	"�ٶֶܶض׶���������ڶ���������"},
{"duo"		,	"����������Ͷ�߶����Զ������������"},
{"e"			,	"������Ŷ���㵶�ج����������湶�������������������������ݭ"},
{"ei"			,	"��"},
{"en"		,	"������"},
{"er"		,	"�����������Ƕ���������ܷ�٦"},
{"fa"		,	"�����������������ҷ�"},
{"fan"		,	"���������������������������������ެ�������"},
{"fang"		,	"���ŷ��÷��·������ݷ�������������"},
{"fei"		,	"�ǷѷɷϷʷȷзƷη˷��������������������������������"},
{"fen"		,	"�ַݷ׷ܷ߷۷շҷطٷ�޷Է�������������"},
{"feng"		,	"�����������������ٺ����ۺ����"},
{"fo"		,	"��"},
{"fou"		,	"���"},
{"fu"		,	"�򸮷����������������������������������������������������������������������ܽ���ڸ����������������������ݳ�������������������������������߻��ۮ�������������"},
{"ga"		,	"���θ¸���٤�������"},
{"gai"		,	"�ĸøŸ�ؤ����������"},
{"gan"		,	"�иɸҸϸʸθ��ϸ��ϸ͸�ߦ���ո���������������"},
{"gang"		,	"�ո۸ָڸٸ׿��ܸԸ������"},
{"gao"		,	"�߸�����޸�غ��޻�ɸݸ�ھ���۬�"},
{"ge"		,	"����������������������������������������تܪ�����������"},
{"gei"		,	"��"},
{"gen"		,	"����ب����ݢ"},
{"geng"		,	"�������������������ṡ�"},
{"gong"		,	"�����������������������������Ź������"},
{"gou"		,	"�������������������������ڸ�������������"},
{"gu"		,	"�ʹŹ˹ɹĹùǹ̹¹ȹ��͹���������������������������������������ڬ������������"},
{"gua"		,	"�ҹϹι��ɹ��Թ������ڴ"},
{"guai"		,	"�ֹԹ���"},
{"guan"		,	"�ع۹ܹٹݹ߹ڹ�޹��ݸ��������������"},
{"guang"		,	"������������"},
{"gui"		,	"����������������������������������Ȳ��������"},
{"gun"		,	"��������޹���"},
{"guo"		,	"���������������������������������"},
{"ha"		,	"������"},
{"hai"		,	"���������ٿȺ�������������"},
{"han"		,	"������������������������������������������ۺ��������������"},
{"hang"		,	"�к��ﺼ���������"},
{"hao"		,	"�úź����ƺ�𩺿껺º����尸�����޶���"},
{"he"		,	"�ͺκϺӺȺպ��źغкǺ̺ɺ��ֺҺ�ڭ����������������������"},
{"hei"		,	"�ں���"},
{"hen"		,	"�ܺ޺ݺ�"},
{"heng"		,	"����ߺ�޿����"},
{"hong"		,	"��������������ްڧޮ����ݦ"},
{"hou"		,	"�����������������ܩ������"},
{"hu"		,	"���������������������������䰻����������������������������������������������������"},
{"hua"		,	"�����������������뻫������"},
{"huai"		,	"������������"},
{"huan"		,	"�������������û��»�����߻��ۼ���ٻ���ۨ�����ߧ�������"},
{"huang"		,	"�ƻʻĻλŻͻ̻л����ɻ˻��������������������"},
{"hui"		,	"��ػ�ӻԻһݻٻڻֻۻ�ջ�߻��޻��ڶ�������������๻������ޥ�������������"},
{"hun"		,	"�������ƻ�ڻ������"},
{"huo"		,	"�ͻ����������������������߫޽�����"},
{"ji"			,	"���������Ǽ��Ƽ����ü������ļʼ����ͻ��漱���̼Ȼ��������������ż����������ɼ���������������ߴ�������˼�����������᧼������ؽڵ����������������������������������٥��ܸآ��ު����������������������������"},
{"jia"		,	"�ҼӼۼټܼ׼Ѽݼм޼μּ���ٮЮ���ļ������٤������ռ��������ۣ����������������������"},
{"jian"		,	"���������������콡�潣������������������������������߼��������Խ���������ﵽ�����������������������������������������"},
{"jiang"		,	"��������������������������筽������������"},
{"jiao"		,	"�̽���У�нϽǽŽ������ν������ɽʽȽ��ý�ٮ�ƽ���毽ѽ˽�𨽶�ͽ��������������Խ�ܴ��������"},
{"jie"		,	"���ӽ�ڽֽ�׽���ܽ�Խݽؽ�ҽٽ߽�޽�������ٽ�ڵ������ڦ�ܽ����������"},
{"jin"		,	"������������������������������������ƽ�����������ݣ���������"},
{"jing"		,	"����������������������������������������㽾���������캾��ɾ�����ݼ������������"},
{"jiong"		,	"����������"},
{"jiu"		,	"�;ž��ƾþɾȾ����ξ˾����ľ�౾������־Ǿ�������"},
{"ju"		,	"�־ݾӾ�پ߾�޾۾ܾ���վоؽ۾ԾϾ׾��ľ���������������ƾ������������������ڪ��︾������������"},
{"juan"		,	"�����������������۲������"},
{"jue"		,	"�������Ž�����Ⱦ��������������Ǿ�������������������ާ��"},
{"jun"		,	"���������������޾������������ܿ�"},
{"ka"		,	"������������"},
{"kai"		,	"�������������������������"},
{"kan"		,	"����٩���������������ݨ�"},
{"kang"		,	"��������������������"},
{"kao"		,	"����������������"},
{"ke"		,	"�ɿ˿ƿͿ̿οſʿºǿ�㡿ȿ��Ŀǿ�����������������������������"},
{"ken"		,	"�Ͽҿп�����"},
{"keng"		,	"�ӿ��"},
{"kong"		,	"�տֿؿ�������"},
{"kou"		,	"�ڿۿٿ�ߵޢ������"},
{"ku"		,	"��޿���ݿ�����ܥ��"},
{"kua"		,	"������٨"},
{"kuai"		,	"���������������ۦ"},
{"kuan"		,	"�����"},
{"kuang"		,	"����������������ڲ��ڿ������"},
{"kui"		,	"��������������ӿ����ѿ������ظ�������������������"},
{"kun"		,	"��������������������"},
{"kuo"		,	"������������"},
{"la"			,	"�����������������������"},
{"lai"		,	"���������������������"},
{"lan"		,	"����������������������������������������"},
{"lang"		,	"�����������������ݹ�������"},
{"lao"		,	"�����������������������������������"},
{"le"			,	"��������߷������"},
{"lei"		,	"����������������������ڳ��������������"},
{"leng"		,	"�������ܨ"},
{"li"			,	"���������������������������������������������������������������ݰ����ٵ��޼ٳ����۪�������������������ت���������޺߿�������������������������������"},
{"lia"		,	"��"},
{"lian"		,	"������������������������������������������������"},
{"liang"		,	"��������������������������ݹܮ�����"},
{"liao"		,	"������������������������������������ޤ��"},
{"lie"		,	"�������������������������"},
{"lin"		,	"���������������������������������������������"},
{"ling"		,	"������������������������������������������������۹������"},
{"liu"		,	"������½������µ��������������������������"},
{"long"		,	"��¡����£����¢����¤�����������"},
{"lou"		,	"¥ª©§�¨��¦��������������"},
{"lu"			,	"·½¼¬¶³¯¹µ®«��­»�±²´��¸��¾������°º��ߣ������ޤ���������������"},
{"lv"			,	"������������������¿�������������������"},
{"luan"		,	"��������������������"},
{"lue"		,	"�����"},
{"lun"		,	"����������������"},
{"luo"		,	"�����������������������������������������������������"},
{"m"		,	"߼"},
{"ma"		,	"��������������Ĩ������������"},
{"mai"		,	"��������������۽ݤ"},
{"man"		,	"�����������������áܬ�������������"},
{"mang"		,	"æãäâåç��������"},
{"mao"		,	"ëðèóìñòéï��î��ê����í��������������"},
{"me"		,	"ô��"},
{"mei"		,	"û��ÿ��ü÷ýö��ú��ùõ��������øݮ�����������þ"},
{"men"		,	"��������������"},
{"meng"		,	"���������������������ޫ�������������"},
{"mi"		,	"��������������������������������������������������������"},
{"mian"		,	"������������������������������"},
{"miao"		,	"�������������������������������"},
{"mie"		,	"��������ؿ�"},
{"min"		,	"�������������������������������"},
{"ming"		,	"����������ڤ�����������"},
{"miu"		,	"����"},
{"mo"		,	"ĬĪģ��ĩĥ��ĦįĮīĨħİ��ĭĤ��Ģ����ġ�������������������"},
{"mou"		,	"ĳı��������ٰ��"},
{"mu"		,	"ĿĸľĻķĽ��ĹļĺĲĶ����Ĵ��ĵ���������"},
{"n"			,	"����"},
{"na"		,	"������������������������"},
{"nai"		,	"����������ܵؾ٦����"},
{"nan"		,	"������������������"},
{"nang"		,	"������߭��"},
{"nao"		,	"����������������ث������"},
{"ne"		,	"��ګ"},
{"nei"		,	"����"},
{"nen"		,	"����"},
{"neng"		,	"��"},
{"ng"		,	"����"},
{"ni"			,	"������������������������������������٣������"},
{"nian"		,	"����إճ�������������������"},
{"niang"		,	"����"},
{"niao"		,	"������������"},
{"nie"		,	"�����������������ؿ�������"},
{"nin"		,	"����"},
{"ning"		,	"����šŢ�������������"},
{"niu"		,	"ţŦŤ�ť������"},
{"nong"		,	"ũŪŨٯ��ŧ"},
{"nou"		,	"��"},
{"nu"		,	"ŭŬū��������"},
{"nv"		,	"Ů������"},
{"nuan"		,	"ů"},
{"nue"		,	"Űű"},
{"nuo"		,	"ŵŲųŴ�������"},
{"o"			,	"Ŷ���"},
{"ou"		,	"ŷżŹŻŸک�źŽ����"},
{"pa"		,	"��������ſž�����������"},
{"pai"		,	"������������ٽ����"},
{"pan"		,	"�����������������������������"},
{"pang"		,	"�������Ұ�����������"},
{"pao"		,	"������������������������"},
{"pei"		,	"�����������������������������"},
{"pen"		,	"������"},
{"peng"		,	"����������������������������ܡ�����"},
{"pi"			,	"����Ƥƨ��ƣ��ơƢƥƧ��Ʃ��Ʀ�����������ۯ���اܱ�����������������ߨ�������������������"},
{"pian"		,	"��Ƭƪƫƭ���������������"},
{"piao"		,	"ƱƯƮư������������ݳ��"},
{"pie"		,	"ƲƳ�د��"},
{"pin"		,	"ƷƶƴƵƸ���������"},
{"ping"		,	"ƽ��ƿƾƼƹ��ƻƺ���ٷ��"},
{"po"		,	"���������²����������������������۶�"},
{"pou"		,	"������"},
{"pu"		,	"�����������������͸��������������������������"},
{"qi"			,	"�������������������������������������������������������������������������������ؽ��������ٹ�����������ܻ������ݽ����������ޭ��������������"},
{"qia"		,	"ǡǢ��٤������"},
{"qian"		,	"ǰǮǧǩǷǣǳǱǨǫǲǸ��ǶǬǴǦ�ǯ�ٻǵǭ���ܷ����ݡ����������ǥǪ���������Ǥ���"},
{"qiang"		,	"ǿǹǽ��ǻǺ����ǼǾ������������������"},
{"qiao"		,	"�����������������������������������ڽ��������������"},
{"qie"		,	"����������������٤����ۧ���"},
{"qin"		,	"��������������������������������������������"},
{"qing"		,	"������������������������������������������������"},
{"qiong"		,	"�����������������"},
{"qiu"		,	"������������������ٴ������������������������"},
{"qu"		,	"ȥȡ����Ȥ����������Ȣ�����������������������ڰ�۾ޡ޾ȣ��������"},
{"quan"		,	"ȫȨȦȰȪȯȭȮڹȧ�������Ȭ������ȩ��"},
{"que"		,	"ȴȷȱȸȳȶȵ����Ȳ��"},
{"qun"		,	"Ⱥȹ����"},
{"ran"		,	"ȻȾȼȽ������"},
{"rang"		,	"��������ȿ���"},
{"rao"		,	"�����������"},
{"re"		,	"������"},
{"ren"		,	"���������������������������������"},
{"reng"		,	"����"},
{"ri"			,	"��"},
{"rong"		,	"������������������������������"},
{"rou"		,	"������������"},
{"ru"		,	"����������������������������޸������"},
{"ruan"		,	"������"},
{"rui"		,	"�������ި�����"},
{"run"		,	"����"},
{"ruo"		,	"����ټ��"},
{"sa"		,	"������ئ�������"},
{"sai"		,	"����������"},
{"san"		,	"��ɢɡ���������"},
{"sang"		,	"ɥɣɤ�����"},
{"sao"		,	"ɨɧɩ����ɦ������ܣ��"},
{"se"		,	"ɫ��ɬɪ����"},
{"sen"		,	"ɭ"},
{"seng"		,	"ɮ"},
{"sha"		,	"ɱɳɶɵ��ɲɴɯɷɰ����������������"},
{"shai"		,	"ɹɸ��"},
{"shan"		,	"ɽ������ɾɿ����ɺɼ�ò���դڨ������������ӵ�������������۷��ɻ�������"},
{"shang"		,	"�������������������������"},
{"shao"		,	"��������������������������ۿ���������"},
{"she"		,	"�����������������������������������"},
{"shei"		,	"˭"},
{"shen"		,	"ʲ�����������������������������ݷ����������ڷ�����������"},
{"sheng"		,	"����ʡʤ��ʥʢʣ����������������"},
{"shi"		,	"��ʱʮ��ʵʹ����ʶʼʿʦʫʽʧʷ��ʾʳ������ʯ��ʩ����ʻ��ʬʰ��ʪ��ʨ��ʴ��ʺ�̳�����������ʸ����ʭ߱����ݪ���������������������"},
{"shou"		,	"�������������������������"},
{"shu"		,	"��������������������������������������������ˡ������������������ٿ������������������ح������"},
{"shua"		,	"ˢˣ�"},
{"shuai"		,	"��˥ˤ˦˧�"},
{"shuan"		,	"��˨˩��"},
{"shuang"	,	"˫ˬ˪����"},
{"shui"		,	"ˮ˭˰˯"},
{"shun"		,	"˳˴˲˱"},
{"shuo"		,	"˵˷˶˸����������"},
{"si"			,	"����˼˹˾��˽˿��˺����˻�������������ٹ�����������������������"},
{"song"		,	"���������������������ݿ����ڡ�"},
{"sou"		,	"����������޴�������������"},
{"su"		,	"���������������������������������������"},
{"suan"		,	"�������"},
{"sui"		,	"�������������������������ݴ�������"},
{"sun"		,	"������ݥ������"},
{"suo"		,	"�������������������������������"},
{"ta"		,	"������̤������̣����̢������������̡"},
{"tai"		,	"̨̧̫̬̩̥̭̦߾��ۢ޷̪����������"},
{"tan"		,	"̸̽��̷̶̹̳̯̰̲̺̱̾̿��̵��̮̻̼�̴���۰����"},
{"tang"		,	"�����������������������������������������������"},
{"tao"		,	"������������������������������ػ"},
{"te"		,	"����߯���"},
{"tei"		,	"߯"},
{"teng"		,	"����������"},
{"ti"			,	"���������������������������������������������"},
{"tian"		,	"���������������������������"},
{"tiao"		,	"��������������٬���������������"},
{"tie"		,	"����������"},
{"ting"		,	"��ͣͥ��ͦͤ��ͧ͢���͡������������"},
{"tong"		,	"ͬͨͳʹͯͮͲͭͰͱͩͫ١��ͪ�����������������"},
{"tou"		,	"ͷͶ͵͸����"},
{"tu"		,	"��ͻͼ;ͽ��Ϳ����ͺ͹ݱ������ܢ"},
{"tuan"		,	"���������"},
{"tui"		,	"������������߯��"},
{"tun"		,	"��������ζ�������"},
{"tuo"		,	"������������������������������ر����٢������������"},
{"wa"		,	"���������۰����������"},
{"wai"		,	"������"},
{"wan"		,	"������������������������������ݸ���������������ܹ���"},
{"wang"		,	"�����������������������������"},
{"wei"		,	"ΪλδίάζΧ����΢ΰνΨΣοβΥκ��εαηθι�ΤΩΡγή�έξ�μ���ޱ������������ΦΫ�������������������������"},
{"wen"		,	"�����������������������������"},
{"weng"		,	"��������޳"},
{"wo"		,	"������������������������ݫ�����"},
{"wu"		,	"������������������������������������������������������أ���������������������������������������������������"},
{"xi"			,	"��ϵϢϣϲϯϰϸϷ��ϴϧϡϤ��Ϧ��Ϯ������Ϫ϶������ϱ��ϨϥۭϬ�����������������ϫ��������ϩ�����ϭ�����������ϳݾ�������������������������"},
{"xia"		,	"������Ͽ������ϼϹϾϺ��Ͻ��ϻ���������������"},
{"xian"		,	"���������������������������������������������������������������ݲ������ϳ�������޺��������"},
{"xiang"		,	"������������������������������������������������������ܼ��"},
{"xiao"		,	"СЦУ��Ч������Ф��Т������Х�����������������������������"},
{"xie"		,	"ЩдлЭЬЯбйвЪгаемжЮик��з�����ߢШ�Ы���ޯ��������������"},
{"xin"		,	"����������нܰ��о�����п���ض"},
{"xing"		,	"���������������������������������ߩ�������"},
{"xiong"		,	"��������������ܺ"},
{"xiu"		,	"���������޳�������������������������"},
{"xu"		,	"�����������������������������������������ڼ�����������������������ޣ"},
{"xuan"		,	"ѡ������ȯ����������Ѥѣ��������������������Ѣ������"},
{"xue"		,	"ѧѪѩ��Ѩ��ѥѦ��������"},
{"xun"		,	"ѰѯѵѸѶѲѷѭѮѬѫѱ��ѳ������������޹Ѵۨ���������ަ��"},
{"ya"		,	"��ѹ����ѽѺ����ѻ��Ѽ��Ѿѿ�����������������������������"},
{"yan"		,	"��������������������������������������������������������ٲ����������������������������������ܾ������������������۱���۳������������"},
{"yang"		,	"�������������������������������������������������"},
{"yao"		,	"Ҫҡҩҫң����ҦҧҢҥ��Ҥز����ߺԿ���������Ҩ���س������������"},
{"ye"		,	"ҲҵҹүҶҰҳҺҮ��ҷק��ҭ��ұҬҴҸ����������"},
{"yi"			,	"һ����������ҽ�������������������������������������������۰�����������������������������������������������������߽߮ܲ����Ҿ�����޲�����������������������������٫��ڱ����Ҽ������������ҿ���������������������"},
{"yin"		,	"������ӡ�������������������������������ط۴������������ܧ������"},
{"ying"		,	"ӦӢӰӪӭӲӳӮӯӱӥӤӬӣӨӫ��ө��ݺ���ӧ����������������۫���������"},
{"yo"		,	"Ӵ�"},
{"yong"		,	"����ӵ��ӿӻӾӹӶӽٸӺ���ӷ����Ӹ�������ܭӼ�"},
{"you"		,	"����������������������������������������������ݬ�������������������������ݯ٧ݵ�����"},
{"yu"		,	"�������������������Ԥ����������������Ԣԥ��������������ԣ����ԡ�����������������Ԧ��������������ع��خ���������������������������������������ٶ������������������������������������"},
{"yuan"		,	"ԱԪԭԺԶԸ԰ԴԲԹԵԮԩԬԨԷԳԧԯԫ������ܾ�����������ܫ�����"},
{"yue"		,	"����ԽԼ��ԾԻ������Կ����������"},
{"yun"		,	"��������������������ܿ�������������۩������"},
{"za"		,	"������զ������"},
{"zai"		,	"��������������������"},
{"zan"		,	"���������������������"},
{"zang"		,	"���������������"},
{"zao"		,	"��������������������������������"},
{"ze"		,	"��������զ�����������������"},
{"zei"		,	"��"},
{"zen"		,	"����"},
{"zeng"		,	"������������"},
{"zha"		,	"ը��զթէգ����դ��բե���������߸ա����������"},
{"zhai"		,	"ժծլխիկ�����"},
{"zhan"		,	"սչվռմնշճյոհ��պտղձջ�����"},
{"zhang"		,	"������������������������������������۵������"},
{"zhao"		,	"�������г���������������گ��������"},
{"zhe"		,	"��������������������������������ߡ������"},
{"zhen"		,	"������������������������������������������������������������"},
{"zheng"		,	"����֤��������֣֢����������������ں����֡"},
{"zhi"		,	"ֻ֪֮����ֱ��ָ֧־ְ��ֵֹֽ֯��ִ����ַ֦��ֲּ��������ֿ֭��ֳ֥֨֫֬��ֶ��ֺ֩������������������������������ش������ۤ�������������������������������"},
{"zhong"		,	"��������������������������ڣ�����"},
{"zhou"		,	"��������������������������������������ݧ������"},
{"zhu"		,	"��סע����������פ��ף��������������������������������������������������������������٪����ۥ��"},
{"zhua"		,	"ץצ"},
{"zhuai"		,	"ק��"},
{"zhuan"		,	"��רת׬׫ש׭�����"},
{"zhuang"	,	"װ״׳ׯײױ��׮������"},
{"zhui"		,	"׷׹׺׶׸��׵�����"},
{"zhun"		,	"׼׻���"},
{"zhuo"		,	"����׽׿������׾����������������پ����ߪ"},
{"zi"			,	"������������������֨�������������������������������������������������������"},
{"zong"		,	"����������������������"},
{"zou"		,	"����������������۸"},
{"zu"		,	"����������������������"},
{"zuan"		,	"׬��߬������"},
{"zui"		,	"������������ީ"},
{"zun"		,	"��������ߤ"},
{"zuo"		,	"�������������������������������������"}

};



static BOOL
InitIme_pinyin();


static void
DestroyIme_pinyin();


static void
ResetIme_pinyin();


static BOOL 
CharArrived_pinyin(
	char c
);

static void
FillBackwardSelection_pinyin();


static void
FillForwardSelection_pinyin();


static char*
GetMatchHZString(
	char* pString
);


static BOOL 
IsBackSpace(
	char ch
);


static BOOL 
IsNumeric(
	char ch
);


static void 
ReCalMatchHZChars();


static void 
ReCalListChars();


LGUIIme pinyinIme = {
	IME_STATUS_PINYIN,
	TASKBAR_IMEBMP_PINYIN,
	InitIme_pinyin,
	DestroyIme_pinyin,
	ResetIme_pinyin,
	CharArrived_pinyin,
	FillBackwardSelection_pinyin,
	FillForwardSelection_pinyin,
	0
};


static BOOL
InitIme_pinyin()
{

	memset(&imeDataTable, 0, sizeof(ImeDataTable));
	return true;
}


static void
DestroyIme_pinyin()
{
	return;
}


static void
ResetIme_pinyin()
{
	memset(&imeDataTable, 0, sizeof(ImeDataTable));
}


static BOOL 
CharArrived_pinyin(
	char ch
)	
{
	char charBuffer[4];
	char* pRes;
	int iIndex;
	if(IsBackSpace(ch)){
		if(imeDataTable.iTotalInputChars == 0){
			//SendMessage(hWndFocus,MSG_KEYDOWN,SCANCODE_BACKSPACE,(LPARAM)NULL);
			SendKeyDown2Client(SCANCODE_BACKSPACE);
		}
		else{
			imeDataTable.iTotalInputChars -- ;
			imeDataTable.pTotalInputChars[imeDataTable.iTotalInputChars] = 0;
			ReCalMatchHZChars();
			ReCalListChars();
		}
	}
	else if(IsNumeric(ch)){
		//select a chinese charater
		iIndex = ch - 0x30;
		if(iIndex + imeDataTable.iBeginPos > imeDataTable.iTotalHZChars){
			memset(imeDataTable.pCurSelected,0,3);
			return true;
		}
		else{
			iIndex = (imeDataTable.iBeginPos + iIndex) * 2;
			imeDataTable.pCurSelected[0] = imeDataTable.pTotalHZChars[iIndex];
			imeDataTable.pCurSelected[1] = imeDataTable.pTotalHZChars[iIndex+1];
			imeDataTable.pCurSelected[2] = 0;
			strcpy(charBuffer, imeDataTable.pCurSelected);	
			SendString2Client(charBuffer);
			//SendMessage(hWndFocus,MSG_CHAR,(WPARAM)charBuffer,(LPARAM)NULL);
			
			imeDataTable.pListChars[0] = 0;
			imeDataTable.iTotalInputChars = 0;
			imeDataTable.pTotalInputChars[0] = 0;
			imeDataTable.iTotalHZChars = 0;
			imeDataTable.pTotalHZChars[0] =0;
			imeDataTable.iBeginPos = 0;	
		}
	}
	else{//

		imeDataTable.pTotalInputChars[imeDataTable.iTotalInputChars] = ch;
		imeDataTable.iTotalInputChars ++;
		imeDataTable.pTotalInputChars[imeDataTable.iTotalInputChars] = 0;
		ReCalMatchHZChars();
		ReCalListChars();
	}
	return true;
}

static void
FillBackwardSelection_pinyin()
{
	if(imeDataTable.iBeginPos == 0)
		return;
	else
		imeDataTable.iBeginPos -= FRAME_CHARS;
	ReCalListChars();

}


static void
FillForwardSelection_pinyin()
{
	if(imeDataTable.iBeginPos + FRAME_CHARS > imeDataTable.iTotalHZChars)
		return;
	else
		imeDataTable.iBeginPos += FRAME_CHARS;
	ReCalListChars();

}


static char*
GetMatchHZString(
	char* pString
)
{
	int i;
	for(i=0;i<MAX_ITEMS;i++){
		if(strcmp(pString, codeTable[i].pPinyin)==0)
			return codeTable[i].pHanzi;
	}
	return NULL;
}


static BOOL 
IsBackSpace(
	char ch
)
{
	if(ch == 8)
		return true;
	else
		return false;
}

static BOOL 
IsNumeric(
	char ch
)
{
	if((ch >= '0') && (ch <='9'))
		return true;
	else
		return false;

}


static void 
ReCalMatchHZChars()
{

	char* pRes;
	char buffer[10];
	strcpy(buffer,imeDataTable.pTotalInputChars);
	//printf("%s\n",buffer);
	pRes = GetMatchHZString(buffer);
	if(!pRes){
		
		imeDataTable.iTotalHZChars = 0;
		imeDataTable.pTotalHZChars[0] = 0;
	}
	else{
		strcpy(imeDataTable.pTotalHZChars,pRes);
		imeDataTable.iTotalHZChars = strlen(imeDataTable.pTotalHZChars);
	}
	imeDataTable.iBeginPos = 0;
	imeDataTable.pReturnHZChars[0] = 0;
	imeDataTable.pCurSelected[0] =0;
	imeDataTable.pListChars[0] = 0;
	
}


static void 
ReCalListChars()
{
	int i;
	char* pListString;
	//according iBeginPos
	pListString = imeDataTable.pListChars;
	//printf("%s\n",imeDataTable.pTotalHZChars);
	for(i = 0; i<FRAME_CHARS; i++){
		if(imeDataTable.iBeginPos + i >= imeDataTable.iTotalHZChars/2 - 1)
			break;
		
			
		pListString[0] = i+0x30;

		pListString[1] = imeDataTable.pTotalHZChars[(imeDataTable.iBeginPos+i) * 2];
		pListString[2] = imeDataTable.pTotalHZChars[(imeDataTable.iBeginPos+i) * 2 + 1];
		
		pListString[3] = ' ';
		pListString += 4;
	}
	*pListString = 0;
	//printf("%s\n",imeDataTable.pListChars);	
		
}













