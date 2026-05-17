#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnGameModeInit() {
	SetTimer("respawnOre", 1000, true);

	CreateDynamicPickup(1274, 23, 1595.9187,1776.9752,10.8047);
	CreateDynamic3DTextLabel("[ Market ]\n{FFFFFF}กด N เพื่อขายแร่", COLOR_YELLOW, 1595.9187,1776.9752,10.8047, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1);
 
	CreateDynamicPickup(1274, 23, 1467.6411,1136.3308,1073.6194);
	CreateDynamic3DTextLabel("[ Procress ]\n{FFFFFF}กด N เพื่อสกัดแร่", COLOR_GREEN, 1467.6411,1136.3308,1073.6194, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1);
 
	new tmpobjid;
	//--> Interior
	tmpobjid = CreateDynamicObject(5772, 1441.435546, 1349.979003, 1079.404541, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 16055, "des_quarry", "desertgravel256", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 16055, "des_quarry", "desertgravel256", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 2, 16640, "a51", "metpat64", 0xFF666666);
	SetDynamicObjectMaterial(tmpobjid, 3, 16175, "des2vegas_join", "vgs_rockmid1a", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 4, 16175, "des2vegas_join", "vgs_rockmid1a", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 5, 19480, "signsurf", "sign", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 6, 16175, "des2vegas_join", "vgs_rockmid1a", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 7, 16644, "a51_detailstuff", "roucghstonebrtb", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 8, 16644, "a51_detailstuff", "roucghstonebrtb", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 9, 16644, "a51_detailstuff", "roucghstonebrtb", 0x00000000);
	tmpobjid = CreateDynamicObject(6252, 1438.329345, 1253.499633, 1073.487060, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 16055, "des_quarry", "desertgravel256", 0xFFFFFFFF);
	SetDynamicObjectMaterial(tmpobjid, 1, 16055, "des_quarry", "desertgravel256", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 2, 16175, "des2vegas_join", "vgs_rockmid1a", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 3, 16175, "des2vegas_join", "vgs_rockmid1a", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 4, 16055, "des_quarry", "desertgravel256", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 5, 16055, "des_quarry", "desertgravel256", 0x00000000);
	tmpobjid = CreateDynamicObject(19378, 1460.620971, 1344.976684, 1073.312255, 0.000000, 90.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 16175, "des2vegas_join", "vgs_rockmid1a", 0x00000000);
	tmpobjid = CreateDynamicObject(19378, 1463.342895, 1344.976684, 1073.312255, 0.000000, 180.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 16175, "des2vegas_join", "vgs_rockmid1a", 0x00000000);
	tmpobjid = CreateDynamicObject(19378, 1460.250610, 1341.976074, 1073.312255, 0.000000, 360.000000, 270.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 16175, "des2vegas_join", "vgs_rockmid1a", 0x00000000);
	tmpobjid = CreateDynamicObject(19378, 1460.160522, 1348.215087, 1073.312255, 0.000000, 360.000000, 270.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 16175, "des2vegas_join", "vgs_rockmid1a", 0x00000000);
	tmpobjid = CreateDynamicObject(19378, 1460.700805, 1344.976684, 1078.223754, 0.000000, 270.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 16175, "des2vegas_join", "vgs_rockmid1a", 0x00000000);
	tmpobjid = CreateDynamicObject(19378, 1460.290527, 1348.135009, 1072.911621, 0.000000, 360.000000, 270.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 18773, "tunnelsections", "metalflooring44-2", 0x00000000);
	tmpobjid = CreateDynamicObject(19378, 1460.270507, 1341.982543, 1072.911621, 0.000000, 360.000000, 270.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 18773, "tunnelsections", "metalflooring44-2", 0x00000000);
	tmpobjid = CreateDynamicObject(19378, 1463.321411, 1343.624023, 1072.921630, 0.000000, 540.000000, 360.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 18773, "tunnelsections", "metalflooring44-2", 0x00000000);
	tmpobjid = CreateDynamicObject(19378, 1460.142944, 1344.114501, 1073.341186, 360.000000, 630.000000, 450.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 18773, "tunnelsections", "metalflooring44-2", 0x00000000);
	tmpobjid = CreateDynamicObject(19378, 1460.142944, 1344.114501, 1078.203247, 360.000000, 630.000000, 450.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 18773, "tunnelsections", "metalflooring44-2", 0x00000000);
	tmpobjid = CreateDynamicObject(19378, 1455.339233, 1345.172973, 1081.873901, 450.000000, 630.000000, 450.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 18800, "mroadhelix1", "concreteoldpainted1", 0x00000000);
	tmpobjid = CreateDynamicObject(19378, 1455.587890, 1338.982421, 1072.911621, 0.000000, 360.000000, 360.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 19278, "skydiveplatforms", "metalpylonred", 0x00000000);
	tmpobjid = CreateDynamicObject(19378, 1455.537841, 1351.283935, 1072.911621, 0.000000, 360.000000, 360.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 19278, "skydiveplatforms", "metalpylonred", 0x00000000);
	tmpobjid = CreateDynamicObject(18227, 1432.958618, 1407.061767, 1070.226806, 10.199984, -159.299850, 100.800346, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFF996666);
	tmpobjid = CreateDynamicObject(19529, 1485.307495, 1159.096557, 1072.573852, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 16055, "des_quarry", "desertgravel256", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(18227, 1498.700195, 1220.008056, 1094.589721, 14.899962, -159.299850, 111.100341, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 12871, "ce_ground01", "rocktbrn128", 0xFFCC9966);
	tmpobjid = CreateDynamicObject(18227, 1511.912475, 1184.446655, 1073.652099, -53.200054, -176.100479, -115.899688, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFF996666);
	tmpobjid = CreateDynamicObject(18227, 1514.376708, 1147.508666, 1087.393554, -53.200054, -176.100479, -116.199768, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFF996666);
	tmpobjid = CreateDynamicObject(18227, 1513.474243, 1097.011962, 1072.566284, -55.299945, -171.100189, 145.700592, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFF996666);
	tmpobjid = CreateDynamicObject(18227, 1450.355957, 1092.705200, 1073.939819, -55.299945, -171.100189, 145.700592, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFF996666);
	tmpobjid = CreateDynamicObject(17031, 1423.997070, 1124.292236, 1071.863891, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 12871, "ce_ground01", "rocktbrn128", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 12871, "ce_ground01", "rocktbrn128", 0x00000000);
	tmpobjid = CreateDynamicObject(17031, 1422.085083, 1172.564208, 1071.863891, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 12871, "ce_ground01", "rocktbrn128", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 12871, "ce_ground01", "rocktbrn128", 0x00000000);
	tmpobjid = CreateDynamicObject(18225, 1401.799072, 1225.466430, 1072.573852, 0.000000, 0.000000, 176.700256, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 12871, "ce_ground01", "rocktbrn128", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 12871, "ce_ground01", "rocktbrn128", 0x00000000);
	tmpobjid = CreateDynamicObject(19529, 1485.307495, 1159.096557, 1093.697753, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 12871, "ce_ground01", "rocktbrn128", 0xFF333333);
	tmpobjid = CreateDynamicObject(900, 1437.802124, 1210.011108, 1086.298095, 111.799636, -11.899986, 24.000043, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 12871, "ce_ground01", "rocktbrn128", 0xFFFF9966);
	tmpobjid = CreateDynamicObject(900, 1444.657104, 1220.699096, 1083.201171, -57.400028, 76.999877, 1.600409, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 12871, "ce_ground01", "rocktbrn128", 0xFF996666);
	tmpobjid = CreateDynamicObject(18227, 1500.910400, 1224.736328, 1085.921630, 14.899962, 20.700149, -47.499767, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 12871, "ce_ground01", "rocktbrn128", 0xFFCC9966);
	tmpobjid = CreateDynamicObject(17031, 1419.328369, 1124.456298, 1084.990600, 0.500000, -56.500026, 178.999938, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 12871, "ce_ground01", "rocktbrn128", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 12871, "ce_ground01", "rocktbrn128", 0x00000000);
	tmpobjid = CreateDynamicObject(17031, 1420.272705, 1178.568115, 1084.518188, 0.500000, -56.500026, 178.999938, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 12871, "ce_ground01", "rocktbrn128", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 12871, "ce_ground01", "rocktbrn128", 0x00000000);
	tmpobjid = CreateDynamicObject(900, 1480.381591, 1184.339843, 1093.646484, -0.799908, 176.100021, 0.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 12871, "ce_ground01", "rocktbrn128", 0xFFCCCCCC);
	tmpobjid = CreateDynamicObject(900, 1456.088378, 1184.316406, 1091.990722, -0.799908, 176.100021, 90.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 12871, "ce_ground01", "rocktbrn128", 0xFFCCCCCC);
	tmpobjid = CreateDynamicObject(18255, 1433.341674, 1132.438964, 1072.573852, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 12871, "ce_ground01", "rocktbrn128", 0x00000000);
	tmpobjid = CreateDynamicObject(18255, 1433.341674, 1175.743774, 1072.573852, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 12871, "ce_ground01", "rocktbrn128", 0x00000000);
	tmpobjid = CreateDynamicObject(900, 1480.381591, 1200.818115, 1093.416259, -0.799908, -164.999694, 90.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 12871, "ce_ground01", "rocktbrn128", 0xFFCCCCCC);
	tmpobjid = CreateDynamicObject(900, 1467.831298, 1200.818115, 1093.242065, -0.799908, -164.999694, 90.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 12871, "ce_ground01", "rocktbrn128", 0xFFCCCCCC);
	tmpobjid = CreateDynamicObject(900, 1445.061279, 1199.448730, 1092.936645, -0.799908, -4.899590, 15.299992, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 12871, "ce_ground01", "rocktbrn128", 0xFFCCCCCC);
	tmpobjid = CreateDynamicObject(900, 1438.991943, 1154.684814, 1092.000854, -0.799908, -4.899590, 15.299992, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 12871, "ce_ground01", "rocktbrn128", 0xFFCCCCCC);
	tmpobjid = CreateDynamicObject(16085, 1471.660644, 1172.459106, 1071.131469, -1.099943, 5.499970, 174.899490, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 12871, "ce_ground01", "rocktbrn128", 0x00000000);
	tmpobjid = CreateDynamicObject(896, 1432.357421, 1115.250244, 1077.351806, 35.099998, -42.299972, 180.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 12871, "ce_ground01", "rocktbrn128", 0xFFCC9999);
	tmpobjid = CreateDynamicObject(896, 1436.168457, 1127.525878, 1084.784179, 33.800018, -29.699859, -162.099685, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 12871, "ce_ground01", "rocktbrn128", 0xFFCC9999);
	tmpobjid = CreateDynamicObject(16112, 1455.304443, 1186.242065, 1063.386718, -0.799997, -11.199991, -19.100229, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 12871, "ce_ground01", "rocktbrn128", 0x00000000);
	tmpobjid = CreateDynamicObject(16112, 1456.406005, 1155.435424, 1061.503295, -0.799997, -11.199991, -19.100229, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 16055, "des_quarry", "desertgravel256", 0xFFCC99FF);
	tmpobjid = CreateDynamicObject(16112, 1487.553466, 1157.016845, 1061.306884, -0.799997, -11.199991, -47.200107, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 16055, "des_quarry", "desertgravel256", 0xFFCC99FF);
	tmpobjid = CreateDynamicObject(19387, 1482.955444, 1134.025024, 1074.302856, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 10756, "airportroads_sfse", "Heliconcrete", 0x00000000);
	tmpobjid = CreateDynamicObject(19377, 1476.613159, 1134.035644, 1072.728881, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 10756, "airportroads_sfse", "Heliconcrete", 0x00000000);
	tmpobjid = CreateDynamicObject(19443, 1483.166259, 1134.047241, 1076.829956, 90.000000, 180.000000, 90.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 10756, "airportroads_sfse", "Heliconcrete", 0x00000000);
	tmpobjid = CreateDynamicObject(3499, 1433.691162, 1210.894042, 1072.342773, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 12870, "ce_ground03", "desclifftypebs", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 16110, "desert", "des_redrock1", 0xFFFF9966);
	tmpobjid = CreateDynamicObject(3499, 1444.598999, 1210.894042, 1072.342773, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 12870, "ce_ground03", "desclifftypebs", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 16110, "desert", "des_redrock1", 0xFFFF9966);
	tmpobjid = CreateDynamicObject(3499, 1439.267578, 1211.161010, 1076.832885, 0.000000, 82.899879, 0.500361, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 16110, "desert", "des_redrock1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 16110, "desert", "des_redrock1", 0xFFFFCC99);
	tmpobjid = CreateDynamicObject(900, 1448.558593, 1138.152954, 1092.674926, -0.799907, -4.899590, 15.299991, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 12871, "ce_ground01", "rocktbrn128", 0xFFCCCCCC);
	tmpobjid = CreateDynamicObject(900, 1473.790771, 1105.124633, 1093.034423, -0.799907, -4.899590, 15.299991, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 12871, "ce_ground01", "rocktbrn128", 0xFFCCCCCC);
	tmpobjid = CreateDynamicObject(18227, 1492.193969, 1232.570922, 1090.181762, 14.899962, 20.700149, -47.499767, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 12871, "ce_ground01", "rocktbrn128", 0xFFCC9966);
	tmpobjid = CreateDynamicObject(1824, 1440.700683, 1212.654174, 1072.953613, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 16055, "des_quarry", "desertgravel256", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 16640, "a51", "sl_metalwalk", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 2, 16640, "a51", "sl_metalwalk", 0x00000000);
	tmpobjid = CreateDynamicObject(1824, 1440.150634, 1251.974853, 1072.953613, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 16055, "des_quarry", "desertgravel256", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 16640, "a51", "sl_metalwalk", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 2, 16640, "a51", "sl_metalwalk", 0x00000000);
	tmpobjid = CreateDynamicObject(1824, 1440.150634, 1297.555297, 1072.953613, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 16055, "des_quarry", "desertgravel256", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 16640, "a51", "sl_metalwalk", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 2, 16640, "a51", "sl_metalwalk", 0x00000000);
	tmpobjid = CreateDynamicObject(1824, 1440.150634, 1324.814941, 1072.953613, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 16055, "des_quarry", "desertgravel256", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 16640, "a51", "sl_metalwalk", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 2, 16640, "a51", "sl_metalwalk", 0x00000000);
	tmpobjid = CreateDynamicObject(1824, 1439.320190, 1372.744873, 1072.953613, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 16055, "des_quarry", "desertgravel256", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 16640, "a51", "sl_metalwalk", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 2, 16640, "a51", "sl_metalwalk", 0x00000000);
	tmpobjid = CreateDynamicObject(1824, 1438.939575, 1390.605346, 1072.953613, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 16055, "des_quarry", "desertgravel256", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 16640, "a51", "sl_metalwalk", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 2, 16640, "a51", "sl_metalwalk", 0x00000000);
	tmpobjid = CreateDynamicObject(1824, 1434.869750, 1390.605346, 1072.953613, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 16055, "des_quarry", "desertgravel256", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 16640, "a51", "sl_metalwalk", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 2, 16640, "a51", "sl_metalwalk", 0x00000000);
	tmpobjid = CreateDynamicObject(1824, 1435.619873, 1361.435668, 1072.953613, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 16055, "des_quarry", "desertgravel256", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 16640, "a51", "sl_metalwalk", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 2, 16640, "a51", "sl_metalwalk", 0x00000000);
	tmpobjid = CreateDynamicObject(1824, 1436.150024, 1315.695678, 1072.953613, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 16055, "des_quarry", "desertgravel256", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 16640, "a51", "sl_metalwalk", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 2, 16640, "a51", "sl_metalwalk", 0x00000000);
	tmpobjid = CreateDynamicObject(1824, 1436.150024, 1288.046020, 1072.953613, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 16055, "des_quarry", "desertgravel256", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 16640, "a51", "sl_metalwalk", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 2, 16640, "a51", "sl_metalwalk", 0x00000000);
	tmpobjid = CreateDynamicObject(1824, 1436.150024, 1243.875244, 1072.953613, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 16055, "des_quarry", "desertgravel256", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 16640, "a51", "sl_metalwalk", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 2, 16640, "a51", "sl_metalwalk", 0x00000000);
	tmpobjid = CreateDynamicObject(1824, 1436.810424, 1213.074829, 1072.953613, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 16055, "des_quarry", "desertgravel256", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 16640, "a51", "sl_metalwalk", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 2, 16640, "a51", "sl_metalwalk", 0x00000000);
	tmpobjid = CreateDynamicObject(1824, 1436.810424, 1218.285156, 1072.953613, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 16055, "des_quarry", "desertgravel256", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 16640, "a51", "sl_metalwalk", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 2, 16640, "a51", "sl_metalwalk", 0x00000000);
	tmpobjid = CreateDynamicObject(1824, 1440.850097, 1218.285156, 1072.953613, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 16055, "des_quarry", "desertgravel256", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 16640, "a51", "sl_metalwalk", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 2, 16640, "a51", "sl_metalwalk", 0x00000000);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	tmpobjid = CreateDynamicObject(3577, 1452.025512, 1333.580932, 1074.155273, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(3577, 1452.025512, 1319.301879, 1074.155273, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(3626, 1450.316772, 1326.797485, 1074.920654, 360.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(3577, 1452.025512, 1363.527954, 1074.155273, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(3577, 1452.025512, 1378.139648, 1074.155273, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(3867, 1452.418212, 1302.378417, 1064.329101, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(3867, 1431.766235, 1265.661621, 1064.629394, 0.000000, 0.000000, 450.000000, -1, -1, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(3867, 1431.766235, 1235.991821, 1064.629394, 0.000000, 0.000000, 450.000000, -1, -1, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(18250, 1480.136718, 1125.043823, 1078.644165, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(18249, 1460.925659, 1126.219848, 1076.883666, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(18248, 1443.766845, 1158.410644, 1080.216918, 0.000000, 0.000000, 37.199848, -1, -1, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(3214, 1459.246948, 1208.309570, 1079.493041, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(16071, 1461.128540, 1192.783081, 1075.643798, 0.000000, 0.000000, 127.799896, -1, -1, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(18227, 1484.260498, 1170.080688, 1117.980102, 104.500000, 82.400047, 98.899955, -1, -1, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(16085, 1432.884643, 1161.653686, 1072.564819, -3.799998, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(16314, 1496.310424, 1157.001708, 1078.409667, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(8879, 1483.483764, 1188.861816, 1078.347534, 0.000000, 0.000000, -173.800277, -1, -1, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(8879, 1495.770263, 1141.677001, 1078.347534, 0.000000, 0.000000, 42.799781, -1, -1, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(8879, 1451.844360, 1140.427490, 1078.347534, 0.000000, 0.000000, -34.300193, -1, -1, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(16309, 1505.954589, 1157.209960, 1077.586547, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(1499, 1482.173828, 1134.081298, 1072.573852, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(3626, 1475.651123, 1131.079223, 1074.124267, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(8879, 1441.391845, 1180.479492, 1078.347534, 0.000000, 0.000000, -134.900177, -1, -1, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(18227, 1484.641479, 1142.157958, 1115.113037, 104.500000, 82.400047, 159.100112, -1, -1, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(18227, 1458.457641, 1103.500244, 1109.362426, 117.999992, 82.400047, 22.900201, -1, -1, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(3504, 1434.885742, 1173.843994, 1073.884887, 0.000000, 0.000000, 450.000000, -1, -1, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(3504, 1434.885742, 1176.163940, 1073.884887, 0.000000, 0.000000, 450.000000, -1, -1, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(1348, 1474.684936, 1134.640136, 1073.306030, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(1431, 1472.644653, 1135.039550, 1073.083740, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(1431, 1476.246826, 1135.529785, 1073.083740, 0.000000, 0.000000, 87.199996, -1, -1, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(923, 1470.549804, 1135.099121, 1073.554565, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(923, 1486.219360, 1135.099121, 1073.554565, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(923, 1489.709472, 1135.099121, 1073.554565, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(3798, 1492.541015, 1137.158935, 1072.593872, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(3798, 1492.541015, 1140.368652, 1072.593872, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(943, 1467.789550, 1135.284301, 1073.444335, 0.000000, 0.000000, -87.500007, -1, -1, -1, 300.00, 300.00); 

	//--> Exterior
	tmpobjid = CreateDynamicObject(18981, 448.315704, -847.379211, 26.297599, 0.000000, 90.000000, 45.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0x00000000);
	tmpobjid = CreateDynamicObject(18981, 448.315704, -847.379211, 28.304950, 0.000000, 90.000000, 45.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 16640, "a51", "stormdrain7", 0x00000000);
	tmpobjid = CreateDynamicObject(18981, 448.315704, -847.379211, 27.294900, 0.000000, 90.000000, 45.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0x00000000);
	tmpobjid = CreateDynamicObject(18808, 463.857116, -832.241760, 28.481010, 0.000000, 90.000000, 45.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 9514, "711_sfw", "shingles2", 0x00000000);
	tmpobjid = CreateDynamicObject(19430, 444.661834, -848.237854, 31.124700, 130.000000, 0.000000, 45.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0x00000000);
	tmpobjid = CreateDynamicObject(19430, 443.951049, -847.529968, 29.246789, 90.000000, 0.000000, 45.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0x00000000);
	tmpobjid = CreateDynamicObject(19430, 444.229156, -847.807861, 30.381399, 105.000000, 0.000000, 45.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0x00000000);
	tmpobjid = CreateDynamicObject(19430, 445.330535, -848.904174, 31.739900, 145.000000, 0.000000, 45.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0x00000000);
	tmpobjid = CreateDynamicObject(19430, 446.198303, -849.769958, 31.939899, 160.000000, 0.000000, 45.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0x00000000);
	tmpobjid = CreateDynamicObject(19430, 446.666625, -850.237060, 31.939899, 17.000000, 0.000000, 45.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0x00000000);
	tmpobjid = CreateDynamicObject(19430, 447.493499, -851.063354, 31.537900, 30.000000, 0.000000, 45.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0x00000000);
	tmpobjid = CreateDynamicObject(19430, 447.938995, -851.508422, 30.729860, 50.000000, 0.000000, 45.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0x00000000);
	tmpobjid = CreateDynamicObject(19430, 448.642974, -852.202514, 28.543769, 70.000000, 0.000000, 45.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0x00000000);
	tmpobjid = CreateDynamicObject(19430, 448.340637, -851.905273, 29.892999, 70.000000, 0.000000, 45.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0x00000000);
	tmpobjid = CreateDynamicObject(14411, 438.902709, -861.275329, 25.600999, 0.000000, 0.000000, -45.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "ws_rooftarmac1", 0x00000000);
	tmpobjid = CreateDynamicObject(19355, 439.221893, -858.206787, 27.050699, 0.000000, 0.000000, -45.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0x00000000);
	tmpobjid = CreateDynamicObject(19355, 438.152801, -859.277038, 27.050699, 0.000000, 0.000000, -45.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0x00000000);
	tmpobjid = CreateDynamicObject(19355, 442.080017, -860.986694, 27.050699, 0.000000, 0.000000, -45.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0x00000000);
	tmpobjid = CreateDynamicObject(19355, 440.969696, -862.095153, 27.050699, 0.000000, 0.000000, -45.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0x00000000);
	tmpobjid = CreateDynamicObject(19377, 438.151275, -861.390808, 5.646669, 0.000000, 10.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10351, "beach_sfs", "rocktb128", 0x00000000);
	tmpobjid = CreateDynamicObject(19377, 441.817840, -861.125915, 5.646699, 0.000000, -10.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10351, "beach_sfs", "rocktb128", 0x00000000);
	tmpobjid = CreateDynamicObject(19377, 440.596160, -856.299072, 5.646699, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10351, "beach_sfs", "rocktb128", 0x00000000);
	tmpobjid = CreateDynamicObject(19377, 441.450988, -861.059509, 7.518380, 0.000000, 90.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "ws_rooftarmac1", 0x00000000);
	tmpobjid = CreateDynamicObject(19377, 433.230804, -866.536865, 5.646699, 0.000000, 10.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10351, "beach_sfs", "rocktb128", 0x00000000);
	tmpobjid = CreateDynamicObject(18762, 438.346588, -866.678039, 8.565349, 0.000000, 10.000000, -45.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10806, "airfence_sfse", "ws_oldpainted", 0x00000000);
	tmpobjid = CreateDynamicObject(18981, 440.895904, -868.296569, 1.215999, 0.000000, 90.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10765, "airportgnd_sfse", "ws_runwaytarmac", 0x00000000);
	tmpobjid = CreateDynamicObject(19377, 432.797363, -870.437988, 5.646699, 0.000000, -10.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10351, "beach_sfs", "rocktb128", 0x00000000);
	tmpobjid = CreateDynamicObject(19377, 436.459655, -870.671630, 7.518380, 0.000000, 90.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "ws_rooftarmac1", 0x00000000);
	tmpobjid = CreateDynamicObject(19377, 431.126708, -869.643676, 5.646699, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10351, "beach_sfs", "rocktb128", 0x00000000);
	tmpobjid = CreateDynamicObject(18762, 438.316345, -870.012573, 8.659629, 0.000000, 10.000000, 45.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10806, "airfence_sfse", "ws_oldpainted", 0x00000000);
	tmpobjid = CreateDynamicObject(18762, 438.818939, -856.252685, 8.785349, 0.000000, 10.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10806, "airfence_sfse", "ws_oldpainted", 0x00000000);
	tmpobjid = CreateDynamicObject(18762, 437.966766, -856.254028, 3.947989, 0.000000, 10.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10806, "airfence_sfse", "ws_oldpainted", 0x00000000);
	tmpobjid = CreateDynamicObject(18762, 441.220764, -856.199890, 8.843549, 0.000000, -10.000000, 359.898986, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10806, "airfence_sfse", "ws_oldpainted", 0x00000000);
	tmpobjid = CreateDynamicObject(18762, 442.088714, -856.196838, 3.947999, 0.000000, -10.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10806, "airfence_sfse", "ws_oldpainted", 0x00000000);
	tmpobjid = CreateDynamicObject(18762, 439.416046, -856.211486, 7.160910, 0.000000, 90.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10806, "airfence_sfse", "ws_oldpainted", 0x00000000);
	tmpobjid = CreateDynamicObject(19377, 437.964233, -875.308898, 5.646669, 0.000000, 10.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10351, "beach_sfs", "rocktb128", 0x00000000);
	tmpobjid = CreateDynamicObject(18762, 437.716156, -870.614501, 3.836800, 0.000000, 10.000000, 45.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10806, "airfence_sfse", "ws_oldpainted", 0x00000000);
	tmpobjid = CreateDynamicObject(19377, 441.816162, -870.734497, 5.646699, 0.000000, -10.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10351, "beach_sfs", "rocktb128", 0x00000000);
	tmpobjid = CreateDynamicObject(18762, 441.519378, -868.516845, 8.681119, 0.000000, -10.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10806, "airfence_sfse", "ws_oldpainted", 0x00000000);
	tmpobjid = CreateDynamicObject(18762, 442.365997, -868.516967, 3.848000, 0.000000, -10.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10806, "airfence_sfse", "ws_oldpainted", 0x00000000);
	tmpobjid = CreateDynamicObject(18981, 440.894317, -893.294616, 1.215999, 0.000000, 90.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10765, "airportgnd_sfse", "ws_runwaytarmac", 0x00000000);
	tmpobjid = CreateDynamicObject(18762, 437.746063, -866.077941, 3.731760, 0.000000, 10.000000, -45.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10806, "airfence_sfse", "ws_oldpainted", 0x00000000);
	tmpobjid = CreateDynamicObject(19377, 447.154998, -875.538330, 5.646699, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10351, "beach_sfs", "rocktb128", 0x00000000);
	tmpobjid = CreateDynamicObject(18762, 441.902740, -875.831665, 9.014780, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10806, "airfence_sfse", "ws_oldpainted", 0x00000000);
	tmpobjid = CreateDynamicObject(18762, 441.902893, -875.829528, 4.049200, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10806, "airfence_sfse", "ws_oldpainted", 0x00000000);
	tmpobjid = CreateDynamicObject(18762, 437.885620, -875.815246, 6.078000, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10806, "airfence_sfse", "ws_oldpainted", 0x00000000);
	tmpobjid = CreateDynamicObject(18762, 437.888671, -875.814880, 1.227309, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10806, "airfence_sfse", "ws_oldpainted", 0x00000000);
	tmpobjid = CreateDynamicObject(19377, 442.152526, -880.265869, 7.518380, 0.000000, 90.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "ws_rooftarmac1", 0x00000000);
	tmpobjid = CreateDynamicObject(19377, 441.903228, -885.031555, 2.399849, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10351, "beach_sfs", "rocktb128", 0x00000000);
	tmpobjid = CreateDynamicObject(19377, 437.964843, -884.911743, 5.646669, 0.000000, 10.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10351, "beach_sfs", "rocktb128", 0x00000000);
	tmpobjid = CreateDynamicObject(19377, 451.510955, -885.031188, 2.399849, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10351, "beach_sfs", "rocktb128", 0x00000000);
	tmpobjid = CreateDynamicObject(19377, 452.652130, -880.171447, 7.518380, 0.000000, 90.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "ws_rooftarmac1", 0x00000000);
	tmpobjid = CreateDynamicObject(18762, 437.876892, -884.739990, 8.968310, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10806, "airfence_sfse", "ws_oldpainted", 0x00000000);
	tmpobjid = CreateDynamicObject(18762, 437.881469, -884.737243, 4.026750, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10806, "airfence_sfse", "ws_oldpainted", 0x00000000);
	tmpobjid = CreateDynamicObject(18762, 440.793792, -866.542419, 7.160910, 0.000000, 90.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10806, "airfence_sfse", "ws_oldpainted", 0x00000000);
	tmpobjid = CreateDynamicObject(18762, 440.615112, -870.297546, 7.160910, 0.000000, 90.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10806, "airfence_sfse", "ws_oldpainted", 0x00000000);
	tmpobjid = CreateDynamicObject(880, 456.626892, -842.803405, 32.818653, 0.000000, 0.000000, 179.199905, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "ws_rooftarmac1", 0x00000000);
	tmpobjid = CreateDynamicObject(18712, 449.949157, -878.012268, 6.032050, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10765, "airportgnd_sfse", "ws_runwaytarmac", 0x00000000);
	tmpobjid = CreateDynamicObject(18676, 453.226348, -880.691162, 4.756663, 0.000000, 0.000000, -167.399963, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10765, "airportgnd_sfse", "ws_runwaytarmac", 0x00000000);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	tmpobjid = CreateDynamicObject(3352, 446.246948, -849.937988, 30.084400, 0.000000, 0.000000, 45.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(10985, 453.034729, -874.512329, 3.637000, 0.000000, 90.000000, 178.577102, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(816, 449.085510, -870.338378, 26.042400, 0.000000, 0.000000, 312.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(816, 452.815612, -871.668884, 26.445400, 0.000000, 0.000000, 212.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(816, 452.820251, -865.801452, 25.536359, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(816, 455.259155, -869.064208, 26.042379, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(816, 448.578674, -876.528320, 24.517099, 0.000000, 0.000000, 1212.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(816, 452.790283, -872.845031, 26.042379, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(867, 453.134857, -854.767150, 28.951290, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(868, 455.820068, -856.030029, 28.780300, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(10985, 415.714111, -844.051879, 25.602899, 0.000000, 0.000000, 122.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(868, 441.687286, -844.320800, 28.780300, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(867, 438.802154, -842.936340, 28.951290, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(683, 428.409179, -840.606079, 23.788930, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(683, 455.107940, -884.297912, 23.788930, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(695, 409.675781, -860.350646, 17.587190, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(849, 435.953216, -844.743469, 29.058200, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(849, 457.627075, -867.287780, 25.524459, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(849, 451.695678, -854.822814, 29.058200, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(849, 444.743041, -876.168029, 24.807249, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(849, 453.927062, -876.945007, 24.765790, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(853, 419.502288, -851.702270, 25.035860, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(853, 406.761657, -846.565612, 25.004110, 0.000000, 0.000000, 0.201000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(853, 450.752655, -866.770751, 26.167219, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(922, 451.294952, -860.408569, 29.700099, 0.000000, 0.000000, 45.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(854, 438.140167, -846.517578, 28.990720, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(854, 450.106109, -859.205200, 28.990720, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(854, 445.448852, -872.950195, 24.853509, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1358, 449.777404, -857.030883, 29.956300, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(867, 418.278198, -851.608154, 24.931369, 0.000000, 0.000000, 0.510100, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(867, 421.449066, -841.599609, 25.205789, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(647, 432.424468, -854.571594, 27.660579, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(647, 409.134216, -855.197021, 25.219139, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(647, 456.350921, -863.213745, 26.292709, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(647, 464.375732, -879.399536, 25.336780, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(647, 407.208221, -869.979980, 23.751640, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(822, 434.994903, -881.774597, 24.316719, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(822, 411.326568, -864.095458, 24.310630, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1358, 434.527862, -848.359985, 29.956300, 0.000000, 0.000000, -450.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(760, 442.406799, -863.367187, 26.531669, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(760, 451.452026, -879.729858, 23.930269, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(822, 408.067871, -832.974304, 24.310630, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(760, 405.017120, -838.851135, 24.642639, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2960, 437.924133, -849.390563, 29.161699, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2960, 447.772521, -858.909912, 29.161699, 0.000000, 0.000000, 121.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2956, 448.390411, -863.401184, 28.799129, 0.000000, 0.000000, 108.106697, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2670, 447.048339, -860.560241, 28.887800, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2670, 441.888366, -848.460266, 28.887800, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2670, 432.448516, -847.952148, 28.887800, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2675, 447.862640, -855.001159, 28.888299, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2675, 438.834655, -850.988891, 28.888299, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(19796, 438.786163, -856.351440, 3.342479, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(851, 448.698303, -876.496765, 1.913100, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(851, 439.177032, -883.433959, 1.913059, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(852, 444.556884, -876.934875, 1.611899, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1462, 445.665283, -876.164062, 1.536649, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1462, 431.660156, -870.208068, 1.536700, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1358, 433.805603, -867.595520, 2.883699, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1355, 433.369964, -870.395751, 1.918699, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1355, 433.727111, -869.680847, 1.918699, 0.000000, 0.000000, 26.095840, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(854, 435.300903, -869.890380, 1.912999, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1264, 435.947692, -866.619628, 2.039400, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1264, 435.941589, -868.237976, 2.019399, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2670, 436.898895, -867.770385, 1.792799, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2228, 440.790985, -884.914978, 2.255599, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2228, 443.394592, -875.672973, 2.255599, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2237, 444.585998, -875.723022, 2.768899, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(952, 447.926788, -883.804504, 3.023099, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(923, 438.186676, -881.166931, 2.620899, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1462, 445.075592, -884.409851, 1.536700, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(960, 444.590454, -883.556884, 2.018899, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(850, 441.812103, -883.519470, 1.814399, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2670, 447.131713, -877.579284, 1.793699, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2670, 444.403778, -882.733947, 1.793699, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2672, 447.560455, -881.456115, 1.993800, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2672, 438.452880, -878.384582, 1.993800, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(960, 439.503631, -880.061401, 2.018899, 0.000000, 0.000000, 347.387207, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(960, 439.399749, -881.664794, 2.018899, 0.000000, 0.000000, 14.576869, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1441, 437.975097, -863.463317, 2.339200, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1440, 441.587249, -873.609191, 2.218549, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2670, 439.359283, -860.951843, 1.811499, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2670, 439.192382, -873.601501, 1.811499, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2672, 441.354370, -858.583679, 1.993299, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2672, 441.272033, -868.771911, 1.993299, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2673, 441.260314, -862.172851, 1.812299, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2673, 438.212493, -868.754638, 1.812299, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(816, 442.563873, -864.274169, 1.712419, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(816, 437.544708, -867.616882, 1.712419, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(816, 445.587158, -881.872253, 1.712419, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(807, 453.567596, -880.697692, 3.256360, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(807, 443.181030, -876.973327, 1.713439, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(816, 438.965087, -857.952453, 1.712419, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(879, 457.266815, -885.326965, 8.380780, 0.000000, 0.000000, 352.479797, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(879, 458.146301, -880.155578, 4.652969, 0.000000, 0.000000, 18.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(906, 452.929077, -878.704284, 6.557990, 0.000000, 0.000000, 0.212310, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(906, 452.582244, -882.482177, 1.710150, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(906, 452.946563, -885.097900, 6.937960, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(868, 453.425872, -883.165832, 4.431280, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(868, 452.526550, -879.040405, 1.733929, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(868, 453.485778, -879.737548, 5.477499, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(879, 459.921508, -884.761596, 3.306699, 0.000000, 0.000000, 18.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(868, 453.800628, -879.329711, 7.087190, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(868, 453.323913, -880.325134, 2.888400, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(868, 453.109954, -875.828491, 6.238550, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(868, 451.972290, -876.178283, 1.733929, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(868, 453.964904, -878.337280, 4.431280, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(807, 448.161895, -878.574462, 1.713439, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(807, 453.653228, -879.318664, 3.794529, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(744, 455.586242, -879.187622, 1.710180, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(744, 453.503417, -877.739379, -1.642349, 0.000000, 0.000000, 359.875762, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(744, 454.505340, -875.847229, 4.281809, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(744, 454.045989, -882.772888, -1.642349, 0.000000, 0.000000, 359.875762, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(807, 450.285186, -880.946960, 1.713439, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(10985, 452.079040, -870.454284, 25.194320, 0.000000, 0.000000, 359.696960, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(879, 457.313385, -888.866210, 3.306679, 0.000000, 0.000000, 352.479797, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(868, 452.969207, -879.909362, 4.431280, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(868, 453.230651, -876.539733, 3.722229, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(879, 460.084045, -884.522399, 5.778279, 0.000000, 0.000000, 18.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(10985, 453.604492, -875.945190, 3.637000, 0.000000, 90.000000, 173.389175, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(880, 450.724060, -840.844116, 33.308647, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(880, 448.762054, -844.358093, 30.478649, 0.000000, 0.000000, 123.100013, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(880, 456.555328, -847.923034, 31.008646, 0.000000, 0.000000, 179.199905, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(879, 443.177001, -835.539489, 30.495048, 0.000000, 0.000000, 53.699966, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(879, 464.336303, -852.882385, 30.495048, 0.000000, 0.000000, 53.699966, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(18712, 440.829254, -869.352294, 6.012049, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(18712, 438.259216, -869.352294, 6.012049, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(18712, 446.149200, -879.862426, 6.032050, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(18712, 440.769195, -860.812438, 6.032050, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(18676, 452.486724, -878.529296, 1.326661, 0.000000, 0.000000, -166.499984, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(18676, 453.168243, -881.368530, 3.426661, 0.000000, 0.000000, 175.100006, -1, -1, -1, 300.00, 300.00);
	return true;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
   	if (newkeys & KEY_NO) {
        //--> ขุดหิน   
        for (new i = 0; i < MAX_SPAWN_ORE; i ++) {
            new Float:x,Float:y,Float:z;
         	GetDynamicObjectPos(spawnOre[i][sOreOBJ],x,y,z);
                                       
			if (IsPlayerInRangeOfPoint(playerid,1.5, x, y, z) && spawnOre[i][sOreID] && spawnOre[i][sOreSpawned]) {
				if(On_Miner_Job[playerid] == 1)
        			return ErrorMsg(playerid, "คุณกำลังขุดแร่อยู่ไม่สามารถขุดซ้ำได้!");

				if (!Inventory_HasItem(playerid, "จอบขุดแร่"))
					return ErrorMsg(playerid, "คุณไม่มีจอบขุดแร่โปรดไปซื้อที่ร้านค้าทั่วไปได้เลย!");

				TogglePlayerControllable(playerid, 0);
				
				//StartProgress(playerid, 200, 0, 0);
				ShowProgressbar(playerid, "Loading...", 10);
				On_Miner_Job[playerid] = 1; 
            }
        }
		if (IsPlayerInRangeOfPoint(playerid, 3.0, 1595.9187,1776.9752,10.8047)) {
			new string100[512];
			new string2[512];

			format(string100, sizeof(string100), "{FFFFFF}ชื่อสินค้า\t{FFFFFF}ราคา\n");
			strcat(string2,string100);

			format(string100, sizeof(string100), "{FFFFFF}แร่เหล็ก\t{FF8800}%d\n", MarketPrice[2]);
			strcat(string2,string100);

			format(string100, sizeof(string100), "{FFFFFF}แร่ทองคำ\t{FF8800}%d\n", MarketPrice[3]);
			strcat(string2,string100);

			format(string100, sizeof(string100), "{FFFFFF}แร่เพรช\t{FF8800}%d\n", MarketPrice[4]);
			strcat(string2,string100);

			format(string100, sizeof(string100), "{FFFFFF}แร่คริสตัล\t{FF8800}%d\n", MarketPrice[5]);
			strcat(string2,string100);

			Dialog_Show(playerid, DIALOG_SELL_MINER, DIALOG_STYLE_TABLIST_HEADERS,"{FFFF00}[ ร้านรับซื้อแร่ ]", string2, "ตกลง","ยกเลิก");
		}        
		if (IsPlayerInRangeOfPoint(playerid, 3.0, 1467.6411,1136.3308,1073.6194)) {
			new amount = Player.Auth[playerid][@item_ore_normal];
			if (amount < 5) {
				return SendClientMessage(playerid, COLOR_RED, "[!] {FFFFFF}คุณมี แร่ท่ัวไป ไม่ถึง 5 ชิ้น");
			}
			TogglePlayerControllable(playerid, false);
			StartProgress(playerid, 120, 0, 0);
			ProgressMiner[playerid] = 1;
			SendClientMessage(playerid, COLOR_RED, "[!] {FFFFFF}คุณได้เริ่มสกัดแร่แล้ว");
			return true;
		}
		return true;
	}
    return true;
}

hook OnProgressFinish(playerid, objectid) {
    /*if(On_Miner_Job[playerid] == 1)
        Player_Miner(playerid);*/

	if (ProgressMiner[playerid] == 1)
		Procress_Miner(playerid);
    
	return Y_HOOKS_CONTINUE_RETURN_0;
}

hook OnProgressUpdate(playerid, progress, objectid) {
   	/*if(On_Miner_Job[playerid] == 1)
	{ 
       ApplyAnimation(playerid, "BASEBALL", "BAT_4", 4.1, 1, 0, 0, 0, 0, 1);
    }*/
	if (ProgressMiner[playerid] == 1) {
		ApplyAnimation(playerid, "BD_FIRE", "WASH_UP", 4.0, 1, 0, 0, 0, 0, 1);
	}
	return Y_HOOKS_CONTINUE_RETURN_0;
}

/*hook UpdtLoading(playerid)
{
	if(LoadingPlayerBar[playerid] >= 100)
	{
		if(On_Miner_Job[playerid] == 1)
        	Player_Miner(playerid);

		if(ProgressMiner[playerid] == 1)
			Procress_Miner(playerid);
	}
	return true;
}*/

stock Player_Miner(playerid) {
   	if (Player.Auth[playerid][@item_ore_normal] + 1 >= Player.Auth[playerid][@itemamount]) {
		ClearAnimations(playerid);
		SendClientMessage(playerid, COLOR_RED, "[!] {FFFFFF}คุณมีช่องเก็บของไม่พอที่จะเก็บแร่ทั่วไป อีก 1 ชิ้น");	
	} else { 
        new A = randomEx(1,2); 
        Player.Auth[playerid][@item_ore_normal] += A;
        ApplyAnimation(playerid, "BSKTBALL", "null", 4.0, 0, 1, 1, 0, 0, 1);
        ApplyAnimation(playerid, "BSKTBALL", "BBALL_pickup", 4.0, 0, 1, 1, 0, 0, 1);

		SendClientMessageEx(playerid, -1, "{0469C8}[!] {FFFFFF}คุณได้รับ (แร่ยังไม่แปรรูป) + %d", A);

        RemovePlayerAttachedObject(playerid, 9);

        for (new i = 0; i < MAX_SPAWN_ORE; i ++) {
            new Float:x,Float:y,Float:z;
            GetDynamicObjectPos(spawnOre[i][sOreOBJ],x,y,z);
            if (IsPlayerInRangeOfPoint(playerid,2, x, y, z)) {
                destroySpawnOre(i);
            }
        }
		On_Miner_Job[playerid] = 0;
    }
    TogglePlayerControllable(playerid, 1);
    return true;
}

stock Procress_Miner(playerid) {
	new B = randomEx(1,2); 
	switch (random(4)) {
		case 0: {
			Player.Auth[playerid][@item_ore_iron] += B;
			SendClientMessageEx(playerid, COLOR_RED, "[!] {FFFFFF}คุณได้รับแร่เหล็กจำนวน %d", B);
		}
		case 1: {
			Player.Auth[playerid][@item_ore_gold] += B;
			SendClientMessageEx(playerid, COLOR_RED, "[!] {FFFFFF}คุณได้รับแร่ทองจำนวน %d", B);
		}
		case 2: {
			Player.Auth[playerid][@item_ore_diamond] += B;
			SendClientMessageEx(playerid, COLOR_RED, "[!] {FFFFFF}คุณได้รับแร่เพรชจำนวน %d", B);
		}
		case 3: {
			Player.Auth[playerid][@item_ore_crystal] += B;
			SendClientMessageEx(playerid, COLOR_RED, "[!] {FFFFFF}คุณได้รับแร่คริสตัลจำนวน %d", B);
		}
	}
	Player.Auth[playerid][@item_ore_normal] -= 5;
	TogglePlayerControllable(playerid, true);
	ProgressMiner[playerid] = 0;
    return true;
}

CMD:reore(playerid, params[]) {
	SetSpawnOre();
	return true;
}

forward respawnOre();
public respawnOre() {
	SetSpawnOre();
    return true;
}

forward SetSpawnOre();
public SetSpawnOre()  {
    for (new i = 0; i < MAX_SPAWN_ORE; i ++)  {
    	if (!spawnOre[i][sOreID]) {
    	    new
	    		index = random(sizeof(oreSpawnLocations));

    	    new
    	        Float:x = oreSpawnLocations[index][0],
    	        Float:y = oreSpawnLocations[index][1],
    	        Float:z = oreSpawnLocations[index][2];

			spawnOre[i][sOreOBJ] = CreateDynamicObject(905, x, y, z-0.5, 0.0, 0.0, 0.0);
       		spawnOre[i][sOreID] = 1;
       		spawnOre[i][sOreSpawn] = index;
        	spawnOre[i][sOreSpawned] = 1;
       	    return i;
		}
    }
    return true;
}

stock destroySpawnOre(idropID)  {
	if (spawnOre[idropID][sOreID]) {
 		spawnOre[idropID][sOreID] = 0;
 		spawnOre[idropID][sOreSpawned] = 0;
  		DestroyDynamicObject(spawnOre[idropID][sOreOBJ]);
  		DestroyDynamic3DTextLabel(spawnOre[idropID][sOreText]);
	}
 	return true;
}

forward OreRespawn(idropID);
public OreRespawn(idropID)  {
	if (spawnOre[idropID][sOreID] && spawnOre[idropID][sOreSpawned]) {
		destroySpawnOre(idropID);
		SetSpawnOre();
	}
}

Dialog:DIALOG_SELL_MINER(playerid, response, listitem, inputtext[]) {
	if (response) {
		switch (listitem) {
			case 0: {
				new iron = Player.Auth[playerid][@item_ore_iron];

				new string[256];

				format(string, sizeof(string), "คุณมีแร่เหล็กจำนวน: [%d]\nราคาปัจจุบัน: 1 ชิ้น/%s\n- กรอกจำนวนที่จะขายด้านล่าง:", iron, FormatNumber(MarketPrice[2]));
				Dialog_Show(playerid, DIALOG_SELL_IRON, DIALOG_STYLE_INPUT, "ขายแร่เหล็ก", string, "ตกลง", "ยกเลิก");
			}
			case 1: {
				new gold = Player.Auth[playerid][@item_ore_gold];

				new string[256];

				format(string, sizeof(string), "คุณมีแร่ทองคำจำนวน: [%d]\nราคาปัจจุบัน: 1 ชิ้น/%s\n- กรอกจำนวนที่จะขายด้านล่าง:", gold, FormatNumber(MarketPrice[3]));
				Dialog_Show(playerid, DIALOG_SELL_GOLD, DIALOG_STYLE_INPUT, "ขายแร่ทองคำ", string, "ตกลง", "ยกเลิก");
			}
			case 2: {
				new diamond = Player.Auth[playerid][@item_ore_diamond];

				new string[256];

				format(string, sizeof(string), "คุณมีแร่เพรชจำนวน: [%d]\nราคาปัจจุบัน: 1 ชิ้น/%s\n- กรอกจำนวนที่จะขายด้านล่าง:", diamond, FormatNumber(MarketPrice[4]));
				Dialog_Show(playerid, DIALOG_SELL_DIAMOND, DIALOG_STYLE_INPUT, "ขายแร่เพรช", string, "ตกลง", "ยกเลิก");
			}
			case 3: {
				new crystal = Player.Auth[playerid][@item_ore_crystal];

				new string[256];

				format(string, sizeof(string), "คุณมีแร่คริสตัลจำนวน: [%d]\nราคาปัจจุบัน: 1 ชิ้น/%s\n- กรอกจำนวนที่จะขายด้านล่าง:", crystal, FormatNumber(MarketPrice[5]));
				Dialog_Show(playerid, DIALOG_SELL_CRYSTAL, DIALOG_STYLE_INPUT, "ขายแร่คริสตัล", string, "ตกลง", "ยกเลิก");
			}
		}
	}
	return true;
}

Dialog:DIALOG_SELL_IRON(playerid, response, listitem, inputtext[]) {
    if (response) {
        new amount = strval(inputtext);

        if (amount <= 0 ||amount > Player.Auth[playerid][@item_ore_iron])
            return ErrorMsg(playerid, "คุณมีแร่เหล็กไม่เพียงพอ");

        Player.Auth[playerid][@item_ore_iron] -= amount;
        new price = amount*MarketPrice[2];
        GivePlayerMoneyEx(playerid, price);
        SendClientMessageEx(playerid, COLOR_YELLOW, "[ขายแร่เหล็ก]: คุณได้ขายแร่เหล็ก จำนวน %d และได้รับเงิน %s", amount, FormatNumber(price));
    }
    return true;
}

Dialog:DIALOG_SELL_GOLD(playerid, response, listitem, inputtext[]) {
    if (response) {
        new amount = strval(inputtext);

        if (amount <= 0 ||amount > Player.Auth[playerid][@item_ore_gold])
            return ErrorMsg(playerid, "คุณมีแร่ทองไม่เพียงพอ");

        Player.Auth[playerid][@item_ore_gold] -= amount;
        new price = amount*MarketPrice[3];
        GivePlayerMoneyEx(playerid, price);
        SendClientMessageEx(playerid, COLOR_YELLOW, "[ขายแร่ทอง]: คุณได้ขายแร่ทอง จำนวน %d และได้รับเงิน %s", amount, FormatNumber(price));
    }
    return true;
}

Dialog:DIALOG_SELL_DIAMOND(playerid, response, listitem, inputtext[]) {
    if (response) {
        new amount = strval(inputtext);

        if (amount <= 0 ||amount > Player.Auth[playerid][@item_ore_diamond])
            return ErrorMsg(playerid, "คุณมีแร่เพรชไม่เพียงพอ");

        Player.Auth[playerid][@item_ore_diamond] -= amount;
        new price = amount*MarketPrice[4];
        GivePlayerMoneyEx(playerid, price);
        SendClientMessageEx(playerid, COLOR_YELLOW, "[ขายแร่เพรช]: คุณได้ขายแร่เพรช จำนวน %d และได้รับเงิน %s", amount, FormatNumber(price));
    }
    return true;
}

Dialog:DIALOG_SELL_CRYSTAL(playerid, response, listitem, inputtext[]) {
    if (response) {
        new amount = strval(inputtext);

        if (amount <= 0 ||amount > Player.Auth[playerid][@item_ore_crystal])
            return ErrorMsg(playerid, "คุณมีแร่คริสตัลไม่เพียงพอ");

        Player.Auth[playerid][@item_ore_crystal] -= amount;
        new price = amount*MarketPrice[5];
        GivePlayerMoneyEx(playerid, price);
        SendClientMessageEx(playerid, COLOR_YELLOW, "[ขายแร่คริสตัล]: คุณได้ขายแร่คริสตัล จำนวน %d และได้รับเงิน %s", amount, FormatNumber(price));
    }
    return true;
}