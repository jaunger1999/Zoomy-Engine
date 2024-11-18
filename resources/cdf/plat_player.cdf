object Plat_Player {
	jumpHeight            1.0
	timeToApex            0.5
	movementSpeed        10.0
	acceleration         10.0
	terminalVelocity      3.0
	neutralJumpDistance   3.0

	states {
		Airborne:
		Ground: PlatPlayer_GroundedMovement
		Sliding:
		GroundPound:
		LongJump:
		DoubleJump:
		SideJump:
		Running:
	}
	
	events {
		land,
		jump,
		crouch
	}
	
	transitions {
		Ground (jump)        Airborne
		Ground (jump|crouch) HighJump
		Running(jump|crouch) LongJump
	}
}