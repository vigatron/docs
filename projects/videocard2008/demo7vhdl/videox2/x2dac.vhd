-- (C) Viktor Glebov 2007

library unisim;
use unisim.vcomponents.roc;

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity x2dac is

		port(	
				SRAM_ADDR	: out std_logic_vector( 18 downto 0 );
				SRAM_DATA	: inout std_logic_vector( 7 downto 0 );
				RAM_CE		: out std_logic;
				RAM_WR		: out std_logic;
				RAM_RD		: out std_logic;
				
				GCLK1 : in std_logic;
				GCLK2 : in std_logic;

				COL: in  std_logic_vector( 7 downto 0 );	-- Input  DATABUS In REFRESH Mode
				DAC: out std_logic_vector( 7 downto 0 );	-- Output DATABUS to DAC
				
				HSYNC,VSYNC : out std_logic;
				
				X2A: in std_logic;
				X2B: in std_logic;
				X2C: in std_logic;
				
				XRES: out std_logic;
				
				XM1: out std_logic;
				XM2: out std_logic
				);

end x2dac;

architecture videoformer of x2dac is

constant VLINES_SYNC_LOW	: INTEGER := 0;
constant VLINES_SYNC_HIGH	: INTEGER := 2;
constant VLINES_VISIBLE 	: INTEGER := 36;
constant VLINES_BACK_PORCH : INTEGER := 512;
constant VLINES_LAST			: INTEGER := 524; -- (1) Include Last

constant PIXELS_HPORCH		: INTEGER := 76;
constant PIXELS_VISIBLE		: INTEGER := PIXELS_HPORCH + 64;
constant PIXELS_HIDDEN		: INTEGER := PIXELS_VISIBLE + 440;
constant PIXELS_LAST			: INTEGER := PIXELS_HIDDEN + 60 - 1;

constant SIG_A : INTEGER := PIXELS_VISIBLE - 2;
constant SIG_C : INTEGER := PIXELS_VISIBLE - 1;
constant SIG_D : INTEGER := PIXELS_HIDDEN - 2;
constant SIG_F : INTEGER := PIXELS_HIDDEN - 1;
constant SIG_V_M3 : INTEGER := PIXELS_VISIBLE - 3;
constant SIG_V_M4 : INTEGER := PIXELS_VISIBLE - 4;
constant SIG_H_M3 : INTEGER := PIXELS_HIDDEN - 3;
constant SIG_H_M4 : INTEGER := PIXELS_HIDDEN - 4;

signal ramptr: 	std_logic_vector( 18 downto 0 );	-- address of the SRAM
signal ramdat: 	std_logic_vector( 7 downto 0 );	
signal rcol:		std_logic_vector( 7 downto 0 );
signal pxlcnt:		std_logic_vector( 9 downto 0 ); -- pixels counter 0...1024
signal lincnt:		std_logic_vector( 9 downto 0 ); -- lines  counter 0...1024
signal clk2:		std_logic;

signal flag_r, flag_w, flag_wd: std_logic;
signal flag_dac, flag_up, flag_vis: std_logic;

begin

-- CLOCK divider
AUTOSTEPCLK: process(GCLK2)
begin
	
	if rising_edge( GCLK2 ) then
		if clk2 = '0'then clk2 <= '1'; else clk2 <= '0'; end if;
	end if;
	
end process;

-- PROCESS HORIZONTAL LINE PIXEL COUNTER
HPXLS: process( GCLK2 )
begin

if rising_edge(GCLK2) then
if clk2 = '1' then

		if pxlcnt = PIXELS_LAST then
		pxlcnt <= ( others => '0' );
		else
		pxlcnt <= pxlcnt + 1; -- (!) BUFFER NEED
		end if;

end if;
end if;
end process;


VLINESCNT: process( GCLK2 )
begin
if rising_edge(GCLK2) then
if clk2 = '1' then
	if pxlcnt = PIXELS_LAST then
		
	if lincnt = VLINES_SYNC_LOW 	then VSYNC <= '0'; end if;
	if lincnt = VLINES_SYNC_HIGH 	then VSYNC <= '1'; flag_up <= X2A;  end if; -- X2A;
	if lincnt = VLINES_VISIBLE 	then flag_vis <= '1'; end if;
	if lincnt = VLINES_BACK_PORCH then flag_vis <= '0'; end if;
	
	if lincnt =  VLINES_LAST then
	lincnt <= (others => '0');
	else
	lincnt <= lincnt + 1;
	end if;
				
	end if;
end if;
end if;
end process;

DETECTMODE: process(GCLK2,pxlcnt)
begin
if rising_edge( GCLK2 ) then

	-- HSYNC CONTROL
	if pxlcnt = 0 then HSYNC <= '0'; end if;
	if pxlcnt = PIXELS_HPORCH then HSYNC <= '1'; end if;

	if flag_vis = '1' then
	
		-- READ MODE
		if pxlcnt = SIG_A and clk2 = '0' and flag_up = '0' then flag_r <= '1'; RAM_CE <= '0'; end if;
		if pxlcnt = SIG_D and clk2 = '0' and flag_up = '0' then flag_r <= '0'; RAM_CE <= '1'; end if;
		
		-- WRITE MODE
		if pxlcnt = SIG_A and clk2 = '1' and flag_up = '1' then flag_w <= '1'; RAM_CE <= '0'; end if;
		if pxlcnt = SIG_D and clk2 = '1' and flag_up = '1' then flag_w <= '0'; RAM_CE <= '1'; end if;
		
		if pxlcnt = SIG_A and clk2 = '0' and flag_up = '1' then flag_wd <= '1'; end if;
		if pxlcnt = SIG_D and clk2 = '0' and flag_up = '1' then flag_wd <= '0'; end if;

		-- EXTERNAL CPLD SYNC
		if pxlcnt = SIG_V_M3 and clk2 = '1' and flag_up = '1' then XM2<= '1'; end if;
		if pxlcnt = SIG_H_M3 and clk2 = '1' and flag_up = '1' then XM2<= '0'; end if;
		
		if pxlcnt = SIG_V_M4 and clk2 = '1' and flag_up = '1' then XM1<= '1'; end if;
		if pxlcnt = SIG_H_M4 and clk2 = '1' and flag_up = '1' then XM1<= '0'; end if;

		-- DAC control
		if pxlcnt = SIG_C and clk2 = '0' then flag_dac <= '1'; end if; -- TURN ON DAC
		if pxlcnt = SIG_F and clk2 = '0' then flag_dac <= '0'; end if; -- TURN OFF DAC
	else
	
		flag_r <= '0';
		flag_dac<= '0';
	
	end if;

end if;
end process;

PROCESSFLAGS: process( GCLK2 )
begin
if rising_edge( GCLK2 ) then

	if lincnt = 0 then
		ramptr <= ( others=>'0' );
		RAM_RD <= '1';
		RAM_WR <= '1';
	end if;
	
	
	if flag_r = '1' then

		if clk2 = '1' then
			SRAM_ADDR <= ramptr;
			SRAM_DATA <= "ZZZZZZZZ";
			RAM_RD <= '0';
		else
			ramptr <= ramptr+1;
			ramdat <= SRAM_DATA;
			RAM_RD <= '1';
		end if;
		
	end if;
	
	if flag_w = '1' then

		if clk2 = '0' then
			SRAM_ADDR <= ramptr;
			SRAM_DATA <= rcol;
			ramdat <= rcol;
			RAM_WR <= '0';
		else
			ramptr <= ramptr+1;
			RAM_WR <= '1';	
		end if;
	
	end if;
	
	if flag_wd = '1' then
	
		if clk2 = '1' then
		rcol <= COL;
		end if;
	
	end if;
	
			
	if flag_dac = '1' then

			if clk2 = '1' then
			DAC <= ramdat;
			end if;
			
	else
			DAC <= ( others => '0' );
	end if;

end if;
end process;

end videoformer;  
