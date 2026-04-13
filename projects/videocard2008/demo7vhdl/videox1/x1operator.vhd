-- (C) Viktor Glebov 2007
-- Functionality : 

-- a). WRITE to 	SRAM
-- b). READ from 	SRAM
-- c). SET HI,MID,LO ADDRESS
-- 
--
-- Out SIGNAL Operation done 
-- Input SIGNAL - Update Mode

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity x1operator is

port(		
			RAM_ADR:	out std_logic_vector(18 downto 0);
			RAM_DAT:	inout std_logic_vector(7 downto 0);
			RAM_CE: out std_logic;
			RAM_WR: out std_logic;
			RAM_RD: out std_logic;

			MCU_DAT:	in std_logic_vector(7 downto 0);
			MCU_CMD: in std_logic_vector(7 downto 0);
			MCU_SWR:	in std_logic;
			
			HSYNC: in std_logic;
			VSYNC: in std_logic;
			
			COL:	out std_logic_vector(7 downto 0);
			
			XM1: in std_logic; -- Inter XILINX (1) connection, remote opstep(low)
			XM2: in std_logic; -- Inter XILINX (2) connection, remote opstep(high)
			
			X1A: in std_logic; -- Connection (A) to MCU ( Update mode )
			X1B: in std_logic; -- Connection (B) to MCU ( Get COLOR ) 
			X1C: in std_logic; -- Connection (C) to MCU

			IRQ0: in std_logic;
			IRQ1: in std_logic;
			FIQ:  in std_logic;

			GCLK1: in std_logic;
			GCLK2: in std_logic );

end x1operator;

architecture videologic of x1operator is

constant cmd_SET_ADDR_HI : std_logic_vector(3 downto 0) := "0001";
constant cmd_SET_ADDR_MD : std_logic_vector(3 downto 0) := "0010";
constant cmd_SET_ADDR_LO : std_logic_vector(3 downto 0) := "0011";
constant cmd_SET_ADDR_ZR : std_logic_vector(3 downto 0) := "0100";
constant cmd_READ_BYTE   : std_logic_vector(3 downto 0) := "0101";
constant cmd_WRITE_BYTE  : std_logic_vector(3 downto 0) := "0110";

signal ramptr 	: std_logic_vector(18 downto 0); -- Pointer to the SRAM
signal ramdat	: std_logic_vector( 7 downto 0); -- 

signal cmdid			: std_logic_vector(3 downto 0);  -- Current command ID
signal cmddone			: std_logic;
signal autostep		: std_logic_vector(1 downto 0); 	-- Current operation counter
signal clk2				: std_logic;

begin

XM1PROC: process( GCLK2 )
begin
if rising_edge(GCLK2) then
	
	-- IN REFRESH MODE ?
	if X1A = '1' then
		if XM1 = '1' then
			if clk2 = '0' then
				RAM_ADR <= ramptr;
				RAM_DAT <= "ZZZZZZZZ";
				RAM_CE <= '0';
				RAM_RD <= '0';
			else
				ramptr <= ramptr + 1;
				ramdat <= RAM_DAT;
				RAM_CE <= '1';
				RAM_RD <= '1';
			end if;
		end if;
	
		if VSYNC = '0' then
		ramptr <= ( others => '0' );
		clk2 <= '0';
		else
		if clk2 = '0' then clk2 <= '1'; else clk2 <= '0'; end if;
		end if;
		
	else

		if MCU_SWR = '1' and cmddone = '0' then
				autostep <= autostep + 1;				
			
					if cmdid = cmd_SET_ADDR_LO	then
						ramptr(7 downto 0) <= ramdat(7 downto 0);
						cmddone <= '1';
					end if;
					
					if cmdid = cmd_SET_ADDR_MD then
						ramptr(15 downto 8) <= ramdat(7 downto 0);
						cmddone <= '1';
					end if;
					
					if cmdid = cmd_SET_ADDR_HI then
						ramptr(18 downto 16) <= ramdat(2 downto 0);
						cmddone <= '1';
					end if;
				
					if cmdid = cmd_SET_ADDR_ZR then
						ramptr <= (others => '0' );
						cmddone <= '1';
					end if;
			
					if cmdid = cmd_WRITE_BYTE then
						if autostep = "00" then RAM_ADR <= ramptr; RAM_DAT <= ramdat; RAM_CE <= '0'; end if;
						if autostep = "01" then ramptr <= ramptr + 1; RAM_WR <= '0'; end if;
						if autostep = "11" then RAM_CE <= '1'; RAM_WR <= '1'; cmddone <= '1'; end if;
					end if;
		
		else
			ramdat <= MCU_DAT;
			cmdid <= MCU_CMD( 3 downto 0 );
			RAM_CE <= '1'; RAM_WR <= '1'; RAM_RD <= '1';
			cmddone <= '0';
			autostep <= ( others => '0' );
		end if;
					
		
	end if;
						

end if;
end process;

XM2PROC: process( GCLK2 )
begin
if rising_edge(GCLK2) then

	if XM2 = '1' then

		if clk2 = '0' then
		COL <= ramdat;
		end if;
	
	end if;

end if;
end process;


end videologic;
