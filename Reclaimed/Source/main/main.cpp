# d e f i n e   W I N 3 2 _ L E A N _ A N D _ M E A N 
 
 # i n c l u d e   < W i n d o w s . h > 
 
 # i n c l u d e   < T l H e l p 3 2 . h > 
 
 
 
 # i n c l u d e   " c s e r i e s \ c s e r i e s . h p p " 
 
 # i n c l u d e   " m e m o r y \ p a t c h i n g . h p p " 
 
 # i n c l u d e   " m a i n . h p p " 
 
 
 
 n a m e s p a c e   b l a m 
 
 { 
 
 	 v o i d   * m o d u l e _ g e t _ b a s e _ a d d r e s s ( ) 
 
 	 { 
 
 	 	 s t a t i c   v o i d   * b a s e _ a d d r e s s   =   n u l l p t r ; 
 
 	 	 i f   ( b a s e _ a d d r e s s   = =   n u l l p t r ) 
 	 	 { 
 	 	 	 a u t o   s n a p s h o t   =   C r e a t e T o o l h e l p 3 2 S n a p s h o t ( T H 3 2 C S _ S N A P M O D U L E ,   G e t C u r r e n t P r o c e s s I d ( ) ) ; 
 
 	 	 	 i f   ( s n a p s h o t   = =   I N V A L I D _ H A N D L E _ V A L U E ) 
 	 	 	 	 r e t u r n   n u l l p t r ; 
 
 	 	 	 M O D U L E E N T R Y 3 2   m o d u l e _ e n t r y ; 
 	 	 	 m o d u l e _ e n t r y . d w S i z e   =   s i z e o f ( M O D U L E E N T R Y 3 2 ) ; 
 
 	 	 	 a u t o   r e s u l t   =   M o d u l e 3 2 F i r s t ( s n a p s h o t ,   & m o d u l e _ e n t r y ) ; 
 	 	 	 C l o s e H a n d l e ( s n a p s h o t ) ; 
 
 	 	 	 b a s e _ a d d r e s s   =   ( r e s u l t   ! =   0 )   ?   ( v o i d   * ) m o d u l e _ e n t r y . m o d B a s e A d d r   :   n u l l p t r ; 
 	 	 } 
 
 	 	 r e t u r n   b a s e _ a d d r e s s ; 
 
 	 } 
 
 
 
 	 c o n s t   a u t o   g a m e _ d i s p o s e   =   ( v o i d ( * ) ( ) ) 0 x 4 2 E 4 1 0 ; 
 
 
 
 	 v o i d   g a m e _ d i s p o s i n g ( ) 
 
 	 { 
 
 	 	 / / 
 
 	 	 / /   T O D O :   f i n a l i z e / d i s p o s e / s h u t d o w n   o t h e r   t h i n g s   h e r e 
 
 	 	 / / 
 
 
 
 	 	 g a m e _ d i s p o s e ( ) ; 
 
 	 } 
 
 
 
 	 v o i d   p a t c h e s _ a p p l y _ c o r e ( ) 
 
 	 { 
 
 	 	 a u t o   m o d u l e _ b a s e _ a d d r e s s   =   ( c h a r   * ) m o d u l e _ g e t _ b a s e _ a d d r e s s ( ) ; 
 
 
 
 	 	 / /   d i s a b l e   t a g   c h e c k s u m s 
 
 	 	 p a t c h _ m e m o r y ( m o d u l e _ b a s e _ a d d r e s s   +   0 x 8 3 9 3 4 ,   " \ x E B " ) ; 
 
 	 	 p a t c h _ m e m o r y ( m o d u l e _ b a s e _ a d d r e s s   +   0 x 8 3 C C 1 ,   " \ x 9 0 \ x 9 0 " ) ; 
 
 	 	 p a t c h _ m e m o r y ( m o d u l e _ b a s e _ a d d r e s s   +   0 x 8 4 7 A B ,   " \ x 9 0 \ x 9 0 " ) ; 
 
 
 
 	 	 / /   d i s a b l e   p r e f e r e n c e s . d a t   c h e c k s u m s 
 
 	 	 p a t c h _ m e m o r y ( m o d u l e _ b a s e _ a d d r e s s   +   0 x 9 F A F 8 ,   " \ x 9 0 \ x 9 0 \ x 9 0 \ x 9 0 \ x 9 0 \ x 9 0 " ) ; 
 
 
 
 	 	 / /   d i s a b l e   - - a c c o u n t   a r g s 
 
 	 	 p a t c h _ m e m o r y ( m o d u l e _ b a s e _ a d d r e s s   +   0 x 3 6 4 9 9 E ,   " \ x E B \ x 0 E " ) ; 
 
 	 	 p a t c h _ m e m o r y ( m o d u l e _ b a s e _ a d d r e s s   +   0 x 3 6 4 9 2 5 ,   " \ x E B \ x 0 3 " ) ; 
 
 
 
 	 	 / /   h o o k   t h e   g a m e _ d i s p o s i n g   f u n c t i o n 
 
 	 	 p a t c h _ c a l l ( m o d u l e _ b a s e _ a d d r e s s   +   0 x 1 5 0 F ,   g a m e _ d i s p o s i n g ) ; 
 
 	 } 
 
 } 
 
 
 
 B O O L   A P I E N T R Y   D l l M a i n ( H M O D U L E ,   D W O R D   r e a s o n ,   L P V O I D ) 
 
 { 
 
         s w i t c h   ( r e a s o n ) 
 
         { 
 
         c a s e   D L L _ P R O C E S S _ A T T A C H : 
 
         c a s e   D L L _ T H R E A D _ A T T A C H : 
 
         c a s e   D L L _ T H R E A D _ D E T A C H : 
 
         c a s e   D L L _ P R O C E S S _ D E T A C H : 
 
                 b r e a k ; 
 
         } 
 
         r e t u r n   T R U E ; 
 
 } 